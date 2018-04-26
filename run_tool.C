{
/*
 * Example list of source and main files from RooUnfold_Kinematics
 *
 * NB: The main is compiled last since it depends on everything else
 *
 *
*/

gROOT->ProcessLine(".L srcs/Particle.cpp+");
gROOT->ProcessLine(".L srcs/Event.cpp+");
gROOT->ProcessLine(".L srcs/EventSelectionTool.cpp+");
gROOT->ProcessLine(".L test/ToolMain.cpp+");
}
