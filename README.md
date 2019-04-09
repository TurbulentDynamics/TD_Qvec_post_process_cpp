# TURBULENT Dyanmics Qvec Post Processing


Turbulent Dynamics specialises in running high-resolution fluid dynamics simulations on supercomputers.  The application decomposes the complete simulation space into smaller grids and each grid is run on one node.  During the simulation each node creates an output file independently.  This applicaiton is used to stitch these files together and do some other post processing calculations.


## Get Started
```
cd Qvec_post_process
git clone https://github.com/TurbulentDynamics/TD_Rushton_Sample_Output_Qvec.git
cmake .
make

./td_Qvec_post_process -v -d TD_Rushton_Sample_Output_Qvec/plot_slice.XZplane.V_4.Q_4.step_00002000.cut_133

#The jupyter notebook in the "python" directory can be used to visualise the file created.
```





## Axes and XYZ Output Planes
The axes and direction are defined with X positive to the right, Y positive downwards and Z positive to the back.  The following image shows the axes and the name of the output planes that cut throught the simulation space.
![XYZ Planes](XYZ_planes.jpg)





