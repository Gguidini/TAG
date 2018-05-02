
#include <bits/stdc++.h>
#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communikation with Gnuplot

using namespace std;
int main(){
    try{
        Gnuplot g1("lines");

        //
        // Slopes
        //
        cout << "*** plotting slopes" << endl;
        g1.set_title("Slopes\\nNew Line");

        cout << "y = x" << endl;
        g1.plot_slope(1.0,0.0,"y=x");

        cout << "y = 2*x" << endl;
        g1.plot_slope(2.0,0.0,"y=2x");

        cout << "y = -x" << endl;
        g1.plot_slope(-1.0,0.0,"y=-x");
        
        g1.set_xlabel("My X Label");
        g1.set_ylabel("My Awesome Y Label");
        
        g1.savetofigure("test_output.ps", "postscript color");
        g1.set_style("lines").set_samples(300).set_xrange(0,5);
        // g1.plot_equation("sin(12*x)*exp(-x)").plot_equation("exp(-x)");

        g1.showonscreen(); // window output
        
        getchar();
    }
    catch (GnuplotException &ge){
        cout << ge.what() << endl;
    }
        
}
