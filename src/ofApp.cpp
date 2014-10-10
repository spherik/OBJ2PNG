#include "ofApp.h"


void ofApp::setup()
{
    string new_path;
    _done = 1;
    
    // Setup fbo
    ofDisableArbTex();
    _fbo.allocate(ofGetWidth(), ofGetHeight());
    _pixels.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    
    _currentFile = 10;
    _path = "/Users/spherik/Dropbox/PhD/Debora - Toni Shared/Paper ACCV/Code/ResultExperiments/Toni_27_09_2014/Interpolacions";
    
    
    ofDirectory dir(_path);
    dir.allowExt("obj");
    dir.listDir();
    
    
    for (int i = 0; i < dir.numFiles(); i++) {
        //ofLogNotice(dir.getPath(i));
        _filesList.push_back(dir.getPath(i));
        new_path = dir.getPath(i);
        ofStringReplace(new_path, "obj", "png");
        _textures.push_back(new_path);
    }
    
    _loader.loadModel(_filesList[_currentFile]);
    cout << "Min: " << _loader.getSceneMin() << endl;
    cout << "Max: " << _loader.getSceneMax() << endl;
    cout << "Center: " << _loader.getSceneCenter() << endl;
    _texture.loadImage(_textures[_currentFile]);
    
    
    _mesh.addVertex(_loader.getSceneMin(false));
    _mesh.addVertex(ofVec3f(_loader.getSceneMin(false)[0], _loader.getSceneMax(false)[1], 0.0));
    _mesh.addVertex(ofVec3f(_loader.getSceneMax(false)[0], _loader.getSceneMax(false)[1], 0.0));
    _mesh.addVertex(ofVec3f(_loader.getSceneMax(false)[0], _loader.getSceneMin(false)[1], 0.0));
    _mesh.addTriangle(0, 1, 2);
    _mesh.addTriangle(0, 2, 3);
    
    
    cout << _mesh.getCentroid() << endl;
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground( 0.0,0.0,0.0 );
    //cout << ofGetCurrentMatrix(OF_MATRIX_MODELVIEW) << endl << "-------------------------" << endl;
    ofPushMatrix();						//Store the coordinate system
    
    //Move coordinate center to screen's center
    ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
    //ofTranslate(_loader.getSceneMin()[0], _loader.getSceneMin()[1], 0.0);
    _mesh.drawWireframe();
    
    _texture.bind();
    //_loader.drawFaces();
    _texture.unbind();
    ofSpherePrimitive(10, 20);
    ofPopMatrix();						//Restore the coordinate system
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
