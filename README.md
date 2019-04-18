# TURBULENT Dyanmics Qvec Post Processing


Turbulent Dynamics specialises in running high-resolution fluid dynamics simulations on supercomputers.  The application decomposes the complete simulation space into smaller grids and each grid is run on one node.  During the simulation each node creates an output file independently.  This applicaiton is used to stitch these files together and do some other post processing calculations.


## Usage
```
USAGE ./td_Qvec_post_process [options] -d <directory>

OPTIONS:
-u     UxUyUz  Calculate and output vectors
-v     Calculate Vorticity, (Three adjecent planes must exist to calculate)
-t     Input json file with Temporal Data Points (for Spectrum)
-o     Overwrite the output files if they exist already

-n     Number of OpenMP threads to be used, reading from shared filesystems with too many threads can be suboptimal
-p     Print verbose information

-d     Directory with the output files


The Plane Qvec output files are named <name>.[XY|XZ|YZ]plane.V_4.Q_<len>.step_<num>.cut_<num>
The angled <name>.rotational_capture.V_4.Q_<len>.step_<num>.angle_<num>.blade_id_<num>
```


## Get Started
```
cd Qvec_post_process
# Clone some sample Qvec data of a Rushton Turbine
git clone https://github.com/TurbulentDynamics/TD_Rushton_Sample_Output_Qvec.git
cmake .
make


export DIR=TD_Rushton_Sample_Output_Qvec

#XY Plane, Low resolution cut through the axis of the tank
./td_Qvec_post_process -v -d ${DIR}/plot_vertical_axis.XYplane.V_4.Q_4.step_00000050.cut_21
./vis.py ${DIR}/plot_axis.YZplane.V_4.Q_4.step_00000050.cut_21


#XZ Plane, Low resolution slice through the tank
./td_Qvec_post_process -v -d ${DIR}/plot_slice.XZplane.V_4.Q_4.step_00000050.cut_29
./vis.py ${DIR}/plot_slice.XZplane.V_4.Q_4.step_00000050.cut_29


#YZ Plane, Low resolution cut through the axis of the tank
./td_Qvec_post_process -v -d ${DIR}/plot_axis.YZplane.V_4.Q_4.step_00000050.cut_21
./vis.py ${DIR}/plot_axis.YZplane.V_4.Q_4.step_00000050.cut_21


#A Medium resolution slice from the central axis to the edge of the tank, 15 degrees behind the impeller
#A sequence of these imaegs would followthe impeller at same 15 degrees behind the impeller
./td_Qvec_post_process -v -d ${DIR}/plot_rotational_capture.rotational_capture.V_4.Q_4.step_00002000.angle_15.blade_id_0
./vis.py ${DIR}/plot_rotational_capture.rotational_capture.V_4.Q_4.step_00002000.angle_15.blade_id_0


#XZ Plane, Medium resolution slice through the tank
./td_Qvec_post_process -v -d ${DIR}/plot_slice.XZplane.V_4.Q_4.step_00002000.cut_133
./vis.py ${DIR}/plot_slice.XZplane.V_4.Q_4.step_00002000.cut_133
```




## Axes and XYZ Output Planes
The axes and direction are defined with X positive to the right, Y positive downwards and Z positive to the back.  The following image shows the axes and the name of the output planes that cut throught the simulation space.
![XYZ Planes](XYZ_planes.jpg)





