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
    
    _currentFile = 2;
    _path = "~/Dropbox/PhD/Debora - Toni Shared/Paper ACCV/Code/ResultExperiments/Toni_27_09_2014/Interpolacions";
    
    
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
    
    for(int i =0; i < _loader.getMesh(0).getVertices().size(); i++)
    {
        bbox.maxX = max(bbox.maxX, _loader.getMesh(0).getVertices()[i][0]);
        bbox.maxY = max(bbox.maxY, _loader.getMesh(0).getVertices()[i][1]);
        bbox.minX = min(bbox.minX, _loader.getMesh(0).getVertices()[i][0]);
        bbox.minY = min(bbox.minY, _loader.getMesh(0).getVertices()[i][1]);
    }
    float diagonal = sqrt((bbox.maxX-bbox.minX)*(bbox.maxX-bbox.minX)+(bbox.maxY-bbox.minY)*(bbox.maxY-bbox.minY));
    
    
    /*cout << "Min: " << _loader.getSceneMin() << endl;
    cout << "Max: " << _loader.getSceneMax() << endl;
    cout << "Center: " << _loader.getSceneCenter() << endl;
    cout << "BBox:" << endl << "* Min: " << bbox.minX << ", " << bbox.minY << endl << "* Max: " << bbox.maxX << ", " << bbox.maxY << endl << "* Center: " << bbox.minX+(bbox.maxX-bbox.minX)/2.0 << ", " << bbox.minY+(bbox.maxY-bbox.minY)/2.0 << endl;*/
    _texture.loadImage(_textures[_currentFile]);
    
    vector<ofVec2f> texCoord;
    _mesh.addVertex(_loader.getSceneMin(false));
    _mesh.addVertex(ofVec3f(_loader.getSceneMin(false)[0], _loader.getSceneMax(false)[1], 0.0));
    _mesh.addVertex(ofVec3f(_loader.getSceneMax(false)[0], _loader.getSceneMax(false)[1], 0.0));
    _mesh.addVertex(ofVec3f(_loader.getSceneMax(false)[0], _loader.getSceneMin(false)[1], 0.0));
    _mesh.addTriangle(0, 1, 2);
    _mesh.addTriangle(0, 2, 3);
    
    texCoord.push_back(ofVec2f(0.0,0.0));
    texCoord.push_back(ofVec2f(0.0,1.0));
    texCoord.push_back(ofVec2f(1.0,1.0));
    texCoord.push_back(ofVec2f(1.0,0.0));
    _mesh.addTexCoords(texCoord);
    
    
    cout << _mesh.getCentroid() << endl;
    
    // Camera
    float viewAngle = 60.0;
    double distance = (diagonal/2.0)/sin((viewAngle*(pi/180)/2.0));
    //std::cout << "Diagonal: " << diagonal << ". Distance: " << distance << endl;
    testCam.setupPerspective(true, viewAngle, 1, distance*1.5, ofVec2f(0.0));
    testCam.setPosition(bbox.minX+(bbox.maxX-bbox.minX)/2.0,bbox.minY+(bbox.maxY-bbox.minY)/2.0,distance);
    testCam.lookAt(ofVec3f(bbox.minX+(bbox.maxX-bbox.minX)/2.0,bbox.minY+(bbox.maxY-bbox.minY)/2.0,0.0), ofVec3f(0.0,1.0,0.0));
    //cout << "MVP: " << testCam.getModelViewMatrix() << endl << "------------------------" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofTrueTypeFont ttf;
    //ttf.loadFont("verdana.ttf", 32, true, true, true);
    ofSetColor(255);
    ofDrawBitmapString("FPS: "+ ofToString((int) ofGetFrameRate()), 10, 20);
    
    
    testCam.begin(ofGetCurrentViewport());
    
    ofBackground( 0.0,0.0,0.0 );
    _texture.bind();
    _mesh.draw();
    _texture.unbind();
    
    _texture.bind();
    //_loader.drawFaces();
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
