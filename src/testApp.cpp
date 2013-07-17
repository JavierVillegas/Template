#include "testApp.h"

#define Nx 640
#define Ny 480


// best contours
bool G_edges = false;
bool G_smooth = false;
IplImage * OutImg;
//--------------------------------------------------------------
void testApp::setup(){
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(Nx,Ny);
    colorImg.allocate(Nx,Ny);
	grayImage.allocate(Nx,Ny);
   // PatternRead.loadImage("UAAZ2mini.png");
    PatternRead.loadImage("two.png");

    PatternColor.allocate(PatternRead.width, PatternRead.height);
    PatternColor.setFromPixels(PatternRead.getPixels(),PatternRead.width,PatternRead.height);
    PatternGray.allocate(PatternRead.width, PatternRead.height);
    PatternGray = PatternColor;
  //  TargetCV.create(PatternRead.width, PatternRead.height, CV_8U);
    TargetCV = cvCreateImage(cvSize(PatternRead.width, PatternRead.height), IPL_DEPTH_8U, 1);
    InputCV = cvCreateImage(cvSize(Nx, Ny), IPL_DEPTH_8U, 1);
    G_LevelsImage = cvCreateImage(cvSize(Nx, Ny), IPL_DEPTH_8U, 1);
    TargetCV = PatternGray.getCvImage();
    Fuente.loadFont("helvetica.ttf", 32);
    G_DetectMode =5;
    OutImg = cvCreateImage(cvSize(Nx-TargetCV->width +1,
                                  Ny-TargetCV->height+1),32,1);

}

//--------------------------------------------------------------
void testApp::update(){
    bool bNewFrame = false;
    
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
	if (bNewFrame){
        
        
        colorImg.setFromPixels(vidGrabber.getPixels(), Nx,Ny);
        grayImage = colorImg;
        //TheInput = colorImg.getCvImage();
        InputCV = grayImage.getCvImage();

        if (G_smooth){
            cvSmooth(InputCV, InputCV,CV_GAUSSIAN,5);
            
        }
        cvMatchTemplate(TargetCV,InputCV,OutImg,CV_TM_CCORR_NORMED);
        
        
        
        

            
            
       
    }

}




//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);

    
    
    ofxCvGrayscaleImage AuxGrayImage;
    AuxGrayImage.allocate(TargetCV->width, TargetCV->height);
    AuxGrayImage = TargetCV;
    AuxGrayImage.draw(0, 0);
    grayImage.draw(AuxGrayImage.width,0);

    cv::Mat Otra(OutImg);
    
    double minVal, maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::Point matchLoc;
    
    minMaxLoc(Otra, &minVal, &maxVal, &minLoc, &maxLoc); //find minimum and maximum intensities

    Otra.convertTo(Otra, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    
 
    
    ofxCvGrayscaleImage AuxGrayImage2;
    AuxGrayImage2.allocate(Otra.cols, Otra.rows);
    AuxGrayImage2 = Otra.data;
    AuxGrayImage2.draw(AuxGrayImage.width+grayImage.width, 0);

    matchLoc = maxLoc;
    ofSetColor(200, 0, 0);
    ofNoFill();
    ofRect(matchLoc.x+AuxGrayImage.width,
           matchLoc.y, AuxGrayImage.width, AuxGrayImage.height);

    ofRect(matchLoc.x+AuxGrayImage.width+grayImage.width-AuxGrayImage.width/2.0,
           matchLoc.y-AuxGrayImage.height/2.0, AuxGrayImage.width, AuxGrayImage.height);
    
    
   // Fuente.drawString(ofToString(G_value), AuxGrayImage.width+Mirona.width+40, 40);
   //Fuente.drawString(ofToString(BestMatches.size()), AuxGrayImage.width+Mirona.width+40, 40);
    
   // Fuente.drawString("Mode: "+ ofToString(G_DetectMode), AuxGrayImage.width+Mirona.width+40, 80);
    
    
   
   
    
    

}












//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch (key) {
        case 'm':
      
            
            G_DetectMode++;
            if (G_DetectMode>8){G_DetectMode=0;}
            break;
     
        case 's':
            G_smooth = !G_smooth;
            break;
        case OF_KEY_RIGHT:
               break;
        case OF_KEY_LEFT:
             
            break;
        case 'e':
            G_edges =!G_edges;
            break;
            
    case 'g':
              break;
        case 'b':
                  break;
           default:  
            break;
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}