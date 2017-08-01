# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.09_FlightSimulator.Debug:
PostBuild.CG1_Tools.Debug: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator
PostBuild.CVK_1_Minimal.Debug: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator
PostBuild.SimpleImage.Debug: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator
PostBuild.CG1_Tools.Debug: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator
PostBuild.CVK_1_Minimal.Debug: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator
PostBuild.SimpleImage.Debug: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator:\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libCG1_Tools.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libCVK_1_Minimal.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libSimpleImage.a\
	/usr/local/lib/libglfw.dylib\
	/usr/local/lib/libGLEW.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libCG1_Tools.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libCVK_1_Minimal.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libSimpleImage.a\
	/usr/local/lib/libglfw.dylib\
	/usr/local/lib/libGLEW.a
	/bin/rm -f /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Debug/09_FlightSimulator


PostBuild.09_FlightSimulator.Release:
PostBuild.CG1_Tools.Release: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator
PostBuild.CVK_1_Minimal.Release: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator
PostBuild.SimpleImage.Release: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator
PostBuild.CG1_Tools.Release: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator
PostBuild.CVK_1_Minimal.Release: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator
PostBuild.SimpleImage.Release: /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator:\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libCG1_Tools.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libCVK_1_Minimal.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libSimpleImage.a\
	/usr/local/lib/libglfw.dylib\
	/usr/local/lib/libGLEW.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libCG1_Tools.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libCVK_1_Minimal.a\
	/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libSimpleImage.a\
	/usr/local/lib/libglfw.dylib\
	/usr/local/lib/libGLEW.a
	/bin/rm -f /Users/mark/Development/cg/CG_demos/BUILD_Xcode/bin/Release/09_FlightSimulator




# For each target create a dummy ruleso the target does not have to exist
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libCG1_Tools.a:
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libCVK_1_Minimal.a:
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Debug/libSimpleImage.a:
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libCG1_Tools.a:
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libCVK_1_Minimal.a:
/Users/mark/Development/cg/CG_demos/BUILD_Xcode/lib/Release/libSimpleImage.a:
/usr/local/lib/libGLEW.a:
/usr/local/lib/libglfw.dylib:
