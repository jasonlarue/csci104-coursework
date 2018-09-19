This guide explains how to configure the Eclipse debugger so that you can debug the robot code in the simulator and on the RoboRio.  The configurations we'll make are specific to a given robot; you'll have to repeat this guide for each robot you want to debug.

First, we need to create build configurations that start the code in debug mode.
## Creating the Build Configurations
1. In Eclipse, click the black down arrow next to the play-button-with-a-toolbox on the top bar, and click "External Tools Configurations..." on the menu that appears.
2. Right-click on your &lt;robot name&gt; Deploy configuration and click Duplicate.
3. Rename the new configuration to "&lt;robot name&gt; Deploy Debug".
4. With the new configuration selected, go to the Targets tab, uncheck `deploy`, and check `debug-deploy`.
5. Hit the Apply button
5. Following the same process, duplicate your "&lt;robot name&gt; Emulator" configuration and select the `debugemulator` target.

Next, we need to tell the IDE how to connect to the debugger.
## Creating the Remote Debugging configurations
1. Click the black down arrow next to the bug on the top bar, and click on "Debug Configurations..."
2. Right-click on `Remote Java Application` in the left pane, and click New
3. Name the new configuration "&lt;robot name&gt; Debug Connect"
4. Click on Browse next to the project box, then select the project for the robot not the common library project 
5. In the Host box type `roborio-3128-frc.local`, and in the port box type `8348`.  Check the "Allow termination of remote VM" box.
6. Hit Apply.
7. Create a new Remote Java Application configuration called "&lt;robot name&gt; Emulator Debug Connect"
8. Select the robot project again
9. Leave the Host at `localhost`, but change the Port to `5433`.  Again, check the "Allow termination of remote VM" box.
10. Hit Apply, and close the dialog box.

To use the configurations, run them once from the Debug Configurations menu, and they'll start appearing in the Debug Configurations pulldown menu.  Note that when you debug the simulator, for some reason it loves to appear _behind_ Eclipse, so you may have to go searching for its dialog box.