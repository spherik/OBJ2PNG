#include "ofApp.h"


void ofApp::setup()
{
    bbox.maxX = std::numeric_limits<float>::min();
    bbox.maxY = std::numeric_limits<float>::min();
    bbox.minX = std::numeric_limits<float>::max();
    bbox.minY = std::numeric_limits<float>::max();
    
    string new_path;
    _done = 1;
    
    // Setup fbo
    ofDisableArbTex();
    _fbo.allocate(ofGetWidth(), ofGetHeight());
    _pixels.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    
    _currentFile = 1;
    _path = "~/Dropbox/PhD/Debora - Toni Shared/Paper ACCV/Code/ResultExperiments/Toni_27_09_2014/Interpolacions";
    
    ofDirectory dir(_path);
    dir.allowExt("obj");
    dir.listDir();
    
    
    for (int i = 0; i < dir.numFiles(); i++) {
        //ofLogNotice(dir.getPath(i));
        _filesList.push_back(dir.getPath(i));
        new_path = dir.getPath(i);
        ofStringReplace(new_path, "obj", "png");
        _texturesList.push_back(new_path);
    }
    
    _loader.loadModel(_filesList[_currentFile]);
    
    for(int i =0; i < _loader.getMesh(0).getVertices().size(); i++)
    {
        bbox.maxX = max(bbox.maxX, _loader.getMesh(0).getVertices()[i][0]);
        bbox.maxY = max(bbox.maxY, _loader.getMesh(0).getVertices()[i][1]);
        bbox.minX = min(bbox.minX, _loader.getMesh(0).getVertices()[i][0]);
        bbox.minY = min(bbox.minY, _loader.getMesh(0).getVertices()[i][1]);
    }
    float diagonal = sqrt((bbox.maxX-bbox.minX)*(bbox.maxX-bbox.minX)+(bbox.maxY-bbox.minY)*(bbox.maxY-bbox.minY));
    
    _texture.loadImage(_texturesList[_currentFile]);
    
    // Camera
    float viewAngle = 30.0;
    double distance = (diagonal/2.0)/sin((viewAngle*(pi/180)/2.0));
    testCam.setupPerspective(true, viewAngle, 1, distance*1.5, ofVec2f(0.0));
    testCam.setPosition(bbox.minX+(bbox.maxX-bbox.minX)/2.0,bbox.minY+(bbox.maxY-bbox.minY)/2.0,distance);
    testCam.lookAt(ofVec3f(bbox.minX+(bbox.maxX-bbox.minX)/2.0,bbox.minY+(bbox.maxY-bbox.minY)/2.0,0.0), ofVec3f(0.0,-1.0,0.0));
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    testCam.begin(ofGetCurrentViewport());
    
    ofBackground( 0.0,0.0,0.0 );
    
    _texture.bind();
    _loader.getMesh(0).drawFaces();
    _texture.unbind();
    
    testCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 's')
    {
        if(_currentFile < _filesList.size())
        {
            _fbo.readToPixels(_pixels);
            string new_path = _filesList[_currentFile];
            ofStringReplace(new_path, ".obj", ".png");
            ofStringReplace(new_path, "meshes", "renders");
            ofSaveImage(_pixels,new_path, OF_IMAGE_QUALITY_BEST);
            _currentFile++;
            _loader.loadModel(_filesList[_currentFile]);
            
            _fbo.allocate(ofGetWidth(), ofGetHeight());
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
