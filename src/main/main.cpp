#include "ofMain.h"
#include "ofApp.h"
#include "ofGLUtils.h"

//========================================================================
int main( ){
	// Happy coding! -Puma
	ofSetupOpenGL(	
		704, 668, 
		OF_WINDOW
	);			
	ofSetWindowTitle("Minecraft Interface Simulator");

	ofRunApp( new ofApp());
}
