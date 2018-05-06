
#include <bits/stdc++.h>
#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communikation with Gnuplot
#define NPOINTS    50 // length of array

using namespace std;
int main(){
    try{
        Gnuplot g1("lines");
        g1.set_xlabel("My X Label");
        g1.set_ylabel("My Awesome Y Label");
         std::vector<double> x, y, y2, dy, z;

        for (unsigned int i = 0; i < NPOINTS; i++)  // fill double arrays x, y, z
        {
            x.push_back((double)i);             // x[i] = i
            y.push_back((double)i * (double)i); // y[i] = i^2
            z.push_back( x[i]*y[i] );           // z[i] = x[i]*y[i] = i^3
            dy.push_back((double)i * (double)i / (double) 10); // dy[i] = i^2 / 10
        }
        y2.push_back(0.00);
        y2.push_back(0.78);
        y2.push_back(0.97);
        y2.push_back(0.43);
        y2.push_back(-0.44);
        y2.push_back(-0.98);
        y2.push_back(-0.77);
        y2.push_back(0.02);

        cout << endl << endl << "*** user-defined lists of doubles" << endl;
        g1.set_style("lines").plot_x(y,"user-defined doubles");
        g1.showonscreen(); // window output
        getchar();

        cout << endl << endl << "*** user-defined lists of points (x,y)" << endl;
        g1.set_grid();
        g1.set_style("points").plot_xy(x,y,"user-defined points 2d");
        g1.showonscreen(); // window output
        getchar();

        g1.reset_plot();
        cout << endl << endl << "*** user-defined lists of points (x,y,z)" << endl;
        g1.unset_grid();
        g1.plot_xyz(x,y,z,"user-defined points 3d");
        g1.showonscreen(); // window output
        getchar();

        g1.reset_plot();
        cout << endl << endl << "*** user-defined lists of points (x,y,dy)" << endl;
        g1.plot_xy_err(x,y,dy,"user-defined points 2d with errorbars");
        g1.showonscreen(); // window output
        getchar();

        // g1.savetofigure("test_output.ps", "postscript color");
        // g1.showonscreen(); // window output
        // getchar();
    }
    catch (GnuplotException &ge){
        cout << ge.what() << endl;
    }
        
}
