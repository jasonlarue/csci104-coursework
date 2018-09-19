# Setting Up the Development Environment

This page will show you how to set up the development environment for robot Java code.

NOTE: Any OS that Eclipse runs on can be used to write and deploy code, but the driver station for controlling the robot only runs on Windows.

## 1: Setting Up Eclipse
1. Download and install the latest Java 8 JDK from here. Make sure to get the 64 bit version if you have a 64 bit PC.
2. If on Windows, download Path Editor, and edit your System Path the bottom pane  to add the `bin` folder of the JDK you just installed it should be in `C:\Program Files\Java\jdk-<whateverversion>\bin` .  This is to make it possible to invoke `java` from the command line. 
3. Download the Eclipse Installer from here.
4. Run it, and choose the `Eclipse IDE for Java Developers`.  Take note of the install location
5. Wait for Eclipse to install.  Don't start it yet.  If the installer starts it, close it.
6. If you are not using Windows, you're done.  Go to the next section.
6. Find the full path to your JDK install folder. It installs to a subfolder in `C:\Program Files\Java`.  Copy the path to the highest-numbered folder in this directory that starts with  "jdk".
7. Set `JAVA_HOME` properly. Go to Control Panel search for it in the Start Menu , and type "system environment" in the search box.  Click on the "Edit the system environment variables" link.
8. In the dialog that pops up, click the Environment Variables button in the bottom right. 
9. In the dialog that pops up, click the "New..." button in the system section at the bottom.
10. In the dialog that pops up, type `JAVA_HOME` for the name, and paste the JDK install path you copied for the value.
11. Hit OK on all three dialogs.
12. If you are not on Windows, you're done! Go to section 2. If you are on Windows, keep going.
6. Find the full filepath to the `bin` subfolder in your **JRE** not JDK  install directory.  The JRE is installed in `C:\Program Files\Java` along with the JDK.

7. Open `eclipse.ini` in the Eclipse install location with a text editor, and add the lines at the top:
```
-vm
<Path to JRE bin folder>
```
Example: 
```
-vm
C:\Program Files\Java\jre1.8.0_66\bin
```
This is to make it possible to pin eclipse to the taskbar.



## 2: Setting up the Eclipse Plugin
1. Open Eclipse.  When it asks to create a workspace, choose a folder, perhaps in your Documents folder.
1. In Eclipse, go to Help > Install New Software...
2. In the dialog that pops up, press the Add... button.  Enter `FRC Eclipse Plugin` as the name and `http://first.wpi.edu/FRC/roborio/release/eclipse/` as the URL.  Press OK.
3. A `WPILib Robot Development` category should pop up in the list.  Expand it, and check `Robot Java Development`.
4. Click next.  It may freeze for a very long time.  This is normal.
5. Click next again, then accept the license agreement and click Finish.
7. Wait for the plugin to install.  Restart Eclipse when prompted, then wait for the "Installing Java toolchain" operation to complete when it comes up.  This is what actually installs the WPI Java SDK.
8. Set your team number.  Open the Eclipse preferences through the title menu `Window > Preferences` on Windows, `Eclipse > Preferences` on mac , and click on "WPILib Preferences" in the left pane.  In the Team Number box, type `3128`.
8. A large portion of the time, the plugin inexplicably fails to create the settings which tell Eclipse where the robot libraries are located.  To see if you have this problem, type `classpath variables` in the top left search box in the preferences window.
9. Click on the "Classpath Variables" entry that shows up in bold in the left pane. Eclipse may hang for a few seconds.  This is expected but strange .
10. There is a box that shows all of the defined classpath variables.  You should see variables starting with `wpilib` and `networktables` with jar icons next to them.  If you do see them, you're done with this section.  Hit OK on the preferences dialog, say yes if asked to perform a full rebuild, and skip to the next section.
11. You're here, so it's broken.  Not to worry, you'll just need to add the four variables manually.  Press the `New...` button next to the list of variables.
12. In the Name textbox, type `wpilib`.
13. Click the `File...` button.  Browse to `<your home directory>/wpilib/java/current/lib` in the file explorer, and select `WPILib.jar`.
14. Press OK on the new variable dialog.
15. Repeat the process three more times, creating a variable `wpilib.sources` pointing to `WPILib-sources.jar`, a variable called `networktables` pointing to `NetworkTables.jar`, and a variable called `networktables.sources` pointing to `NetworkTables-sources.jar`.
16. Done! Press OK on the preferences dialog.  If it asks if you want to rebuild, say yes.


## 3: Cloning the Team Core Repo
1. Download Github Desktop, if you don't have it already.
2. Create a GitHub account.  Log in to Github Desktop app and the GitHub website.
2. Go to the common repository. Press the green "Clone or download" button in the top left, and click the "Open in Desktop" button.  When it asks where to clone it, choose the Eclipse workspace folder you selected.
3. In Eclipse, choose File>Import...  On the dialog that pops up, choose General > Existing Projects into Workspace
4. Press Next.  Click the Browse... button next to "Select root directory" and choose your workspace folder.
5. Check the box for `3128-robot-common`
6. Hit finish.

## 4: Setting up a Robot Program
1. To actually deploy code on a robot, you need to clone the code repository for it.  For example, our 2016 robot code is here. In Github Desktop, clone the robot code repository into the same folder as the core repo.
2. Import the project into Eclipse, the same way as in the previous section.
3. Create the Ant build configuration.  Click on the down arrow next to the play button with a toolbox on the top bar of eclipse, and select `External Tools Configurations...`
4. Click on "Ant Build" in the left pane, and click on the page icon in the top left to create a new Ant build configuration.
5. Name it "&lt;Robot Name&gt; Deploy" &lt;Robot Deploy&gt; = the name of the robot  in the textbox at the top.
6. In the Main tab, click on `Browse Workspace...` in the Buildfile section.  Select the `build.xml` file in the root of the repository you just cloned.
7. Go to the Targets tab.
8. Make sure `deploy` and only `deploy` is checked in the list of targets.
9. Hit Apply in the bottom right corner to save the build configuration.
10. Now, set up the simulator configuration.  Repeat steps 4 through 6, but name your configuration "&lt;Robot Name&gt; Simulator"
11. Go to the Targets tab, uncheck `deploy`, and check `runemulator`.
12. Save your configuration, and run it.  The simulator should come up.

## 5: Creating a New Robot Program
1. Download the template project
2. Extract it into your eclipse workspace.
3. Rename the folder to what you want your robot program to be called.
4. Import the project into Eclipse.
5. Rename MainTemplate to match your program name.
6. Edit robot-code.properties in the root folder of the project and change the `robot.class` line to point to the new name of the main class.  This name is relative to the `org.team3128` package
7. Create the build configurations.  You can copy them from another project and change the project and `build.xml`, or create them from scratch as described in steps 3-12 in the previous section
8. Code away!

# Troubleshooting
*Help!  It doesn't work!*

| Symptom | Problem | Fix |
| ------- | ------- | --- |
| There are red exclamation marks next to all my projects!  In the Problems window, it says things like `unbound classpath variable: wpilib`! | The classpath variables are not set up properly. | Open Preferences in Eclipse and complete steps 9-17 of section 2.  If you've already done this, than you probably messed up somewhere. |
| There are *still* red exclamation marks, and I'm sure I set up the classpath properly! | The common library project could not be found. | Check that the common library project is imported into eclipse, and is named `3128-robot-common`. If it has a `-master` suffix, you just downloaded the zip from GitHub instead of cloning it with GitHub desktop, didn't you!  Re-do section 3 properly.  If is called something other than `3128-robot-common`, right-click the project and `Refactor > Rename` it to `3128-robot-common`.
| When I try to build, I get the error `build-common.xml:13: classloader doesn't support the "loader" attribute` | You are trying to build the 3138-robot-common `build-common.xml` file in a build configuration.  This file is supposed to be included by the robot code projects' build files.  These files define a property telling the script where to find its config file, and when this property is not defined, Bad Things happen. | Select one of the robot code projects' `build.xml` files in your ant configurations |
| When I try to deploy to the robot, I get an error message like `loadfile: cannot load file sysProps.xml` | The build script could not connect to the roboRIO.  Sometimes it gives this error instead of a more descriptive one. | Make sure that you can connect to the robot.  Are you on the right wifi network?  Can you ping `roborio-3128-frc.local`? |
| When I try to create the ant build configurations in section 4, the target list is blank! | The robot code project is not in the same folder as the common library, or the common library is not named `3128-robot-common`.  The robot code projects include the build script from the common library, so the common library has to have a known name and location. | Make sure that the common library and robot code projects are all in the same folder.  It's not enough for them to be in the same Eclipse workspace, they have to be in the same folder. | If the common library is named `3128-robot-common-master`, you just downloaded the zip file from GitHub instead of cloning the common library in GitHub Desktop.  Re-do section 3 properly. |
| When I press the Open in Desktop button on the GitHub site, it just redirects me to the GitHub Desktop download page! | You must be logged in to GitHub for this to work. | Log in to the GitHub website.  Check that GitHub Desktop is set up and working. |

Also try: [Setting up robot debugging](wiki/controls/guides/Setting-Up-Robot-Debugging.md)