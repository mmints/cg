# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.CG1_Tools.Debug:
/Users/mark/Development/cg/CG/BUILD_Xcode/lib/Debug/libCG1_Tools.a:
	/bin/rm -f /Users/mark/Development/cg/CG/BUILD_Xcode/lib/Debug/libCG1_Tools.a


PostBuild.CG1_Tools.Release:
/Users/mark/Development/cg/CG/BUILD_Xcode/lib/Release/libCG1_Tools.a:
	/bin/rm -f /Users/mark/Development/cg/CG/BUILD_Xcode/lib/Release/libCG1_Tools.a




# For each target create a dummy ruleso the target does not have to exist
