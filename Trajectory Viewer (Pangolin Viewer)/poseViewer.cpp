#include <pangolin/pangolin.h>
#include <Eigen/Core>
#include <unistd.h>


using namespace std;
using namespace Eigen;

// path to trajectory file
string trajectory_file = "../../Trajectory Viewer (Pangolin Viewer)/trajectory.txt";

void DrawTrajectory(vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>>);

int main(int argc, char **argv) {

    vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses;
    ifstream fin(trajectory_file);
    if (!fin) {
        cout << "cannot find trajectory file at " << trajectory_file << endl;
        return 1;
    }

    while (!fin.eof()) {
        double time, tx, ty, tz, qx, qy, qz, qw;
        fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
        Isometry3d Twr(Quaterniond(qw, qx, qy, qz));
        Twr.pretranslate(Vector3d(tx, ty, tz));
        poses.push_back(Twr);
    }
    cout << "read total " << poses.size() << " pose entries" << endl;

    // draw trajectory in pangolin
    DrawTrajectory(poses);
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses) {
    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));

    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(2);

        glColor4f(0.1, 0.1, 0.1,0.4f);
        glBegin(GL_LINES);
        for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
            glVertex3f(i, 2.5, 0); glVertex3f(i, -2.5, 0);
            glVertex3f(2.5, i, 0); glVertex3f(-2.5, i, 0);
        }

        glLineWidth(10);

        glColor3f(0.0, 1.0, 0.0);

        glVertex3f(0, 0, 0); glVertex3f(0, 0, 0.5);


        glColor3f(1.0, 0.0, 0.0);

        glVertex3f(0, 0, 0); glVertex3f(0, 0.5, 0);

        glColor3f(0.0, 0.0, 1.0);

        glVertex3f(0, 0, 0); glVertex3f(0.5, 0, 0);
        glEnd();

        // Draw the connection
        for (size_t i = 0; i < poses.size(); i++) {


            glPointSize(1.5*7);
            glBegin(GL_POINTS);
            auto p1 = poses[i];
            glColor4f(1.0, 0.0, 1.0, 1);
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glEnd();
//
//            glBegin(GL_POINTS);
//            glPointSize(6*7);
//            glColor4f(1.0, 0.0, 0.0, 0.4);
//            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
//            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }
}