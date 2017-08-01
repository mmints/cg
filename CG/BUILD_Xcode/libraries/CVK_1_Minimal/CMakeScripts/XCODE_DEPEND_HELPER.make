# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.CVK_1_Minimal.Debug:
/Users/mark/Development/cg/CG/BUILD_Xcode/lib/Debug/libCVK_1_Minimal.a:
	/bin/rm -f /Users/mark/Development/cg/CG/BUILD_Xcode/lib/Debug/libCVK_1_Minimal.a


PostBuild.CVK_1_Minimal.Release:
/Users/mark/Development/cg/CG/BUILD_Xcode/lib/Release/libCVK_1_Minimal.a:
	/bin/rm -f /Users/mark/Development/cg/CG/BUILD_Xcode/lib/Release/libCVK_1_Minimal.a




# For each target create a dummy ruleso the target does not have to exist
