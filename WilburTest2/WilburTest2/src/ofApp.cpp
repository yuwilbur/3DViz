#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	// load in sounds:
	input_music_.loadSound("../../../../3DViz/bin/data/sounds/Journeyman.mp3");
	input_music_.play();

	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}

	amplitude_limit_ = 500.0f;
	average_amplitude_ = 0.0f;
	prev_average_amplitude_ = 0.0f;
	nBandsToGet = 128;
	BG_R_ = 255;
	BG_G_ = 0;
	BG_B_ = 0;

	std::string imageURL = findImage();
	std::cout << imageURL << std::endl;
	ofRegisterURLNotification(this);

    image_.clear();
    ofLoadURLAsync(imageURL.c_str(), "test");
    //ofLoadURLAsync("https://fbcdn-sphotos-h-a.akamaihd.net/hphotos-ak-xfp1/t1.0-9/10452314_10152317691815369_2723406659431248531_n.jpg","test");
    loading = true;
}

void ofApp::urlResponse(ofHttpResponse & response) {
    if (response.status == 200 && response.request.name == "test") {
        image_.loadImage(response.data);
        loading = false;
    } else {
        std::cout << response.status << " " << response.error << std::endl;
        if (response.status != 1 ) loading = false;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
	// update the sound playing system:
	ofSoundUpdate();
	// (5) grab the fft, and put in into a "smoothed" array,
	//		by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){

		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;

		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

	}

	updateColor(BG_R_, BG_G_, BG_B_);
	float BG_R = BG_R_;
	float BG_G = BG_G_;
	float BG_B = BG_B_;
	amplifyColor(BG_R, BG_G, BG_B);

	ofBackground(BG_R,BG_G,BG_B);
}

void ofApp::exit() {
    ofUnregisterURLNotification(this);
}

std::string ofApp::findImage() {
    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in C++, it will be given a block of memory. This memory is not necessary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof host_info);

    std::cout << "Setting up the structs..."  << std::endl;

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    // Now fill up the linked list of host_info structs with google's address information.
    status = getaddrinfo("127.0.0.1", "5000", &host_info, &host_info_list);
    // getaddrinfo returns 0 on succes, or some other value when an error occured.
    // (translated into human readable text by the gai_gai_strerror function).
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;

    std::cout << "Creating a socket..."  << std::endl;
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;

    std::cout << "Connect()ing..."  << std::endl;
    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "connect error" ;

    std::cout << "send()ing message..."  << std::endl;
    char *msg = "GET /images/taylor HTTP/1.1\nhost: www.google.com\n\n";
    int len;
    ssize_t bytes_sent;
    len = strlen(msg);
    bytes_sent = send(socketfd, msg, len, 0);

    std::string str;

    std::cout << "Waiting to recieve data..."  << std::endl;
    ssize_t bytes_recieved;
    char incoming_data_buffer[100];
    bytes_recieved = recv(socketfd, incoming_data_buffer,100, 0);


    while (bytes_recieved > 0) {
        // If no data arrives, the program will just wait here until some data arrives.

        std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
        //std::cout << incoming_data_buffer << std::endl;
        str.append(incoming_data_buffer);
        memset(&incoming_data_buffer, 0, sizeof incoming_data_buffer);
        bytes_recieved = recv(socketfd, incoming_data_buffer,100, 0);
    }

    if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
    if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;

    char* httpbody;
    httpbody = strstr(incoming_data_buffer, "\r\n\r\n");
    if(httpbody) {
        httpbody += 4;
        std::cout << httpbody << std::endl;
    }

    //std::cout << str << std::endl;


    //isolate json array
    std::size_t endFound = str.find("}]");
    std::size_t startFound = str.find("[{");
    if (startFound!=std::string::npos && endFound!=std::string::npos) {
        std::cout << str.substr(startFound, endFound + 2 - startFound) << std::endl;
    }

    //json parsing
    //std::string* urlArray = (std::string*)malloc(sizeof(std::string)*100);
    std::vector<std::string> urlArray;
    std::size_t startPos = str.find("\"url\":");
    std::size_t endPos = str.find("\"height\":");
    int i = 0;
    while (startPos!=std::string::npos && endPos!=std::string::npos) {
        urlArray.push_back(str.substr(startPos + 8, endPos - 11 - startPos));
        //std::cout << urlArray[urlArray.size() - 1] << std::endl;
        //str.erase(str.begin(), endPos);
        str = str.substr(endPos + 5, sizeof(str) - endPos);
        i++;
        startPos = str.find("\"url\":");
        endPos = str.find("\"height\":");
    }
    if (urlArray.size() > 0) {
        std::string chars = "1234567890qwertyiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM._-#?!&:\//";
        std::string output = urlArray[0];
        for (int i = 0; i < output.size(); ++i) {
            bool is_bad_char = true;
            for (int j = 0; j < chars.size(); ++j) {
                if (output[i] == chars[j]) {
                    is_bad_char = false;
                    break;
                }
            }
            if (is_bad_char) {
                output.erase(i,2);
            }
        }
        return output;
    } else {
        return "";
    }
}

void ofApp::updateColor(float& R, float& G, float& B) {

	float spectrum_increment = 0.25f;

	if (R >= 255 && G < 255 && B <= 0) {
		G += spectrum_increment; // 255,0,0 -> 255,255,0
	} else if (R > 0 && G >= 255 && B <= 0) {
		R -= spectrum_increment; // 255,255,0 -> 0,255,0
	} else if (R >= 0 && G >= 255 && B < 255) {
		B += spectrum_increment; // 0,255,0 -> 0,255,255
	} else if (R >= 0 && G > 0 && B >= 255) {
		G -= spectrum_increment; // 0,255,255 -> 0,0,255
	} else if (R < 255 && G <= 0 && B >= 255) {
		R += spectrum_increment; // 0,0,255 -> 255,0,255
	} else if (R >= 255 && G <= 0 && B > 0) {
		B -= spectrum_increment; // 255,0,255 -> 255,0,0
	}
}

void ofApp::amplifyColor(float& R, float& G, float& B) {
	float amplitude_ratio = average_amplitude_ / amplitude_limit_ * 4;
	amplitude_ratio = std::min(1.0f, std::max(0.1f, amplitude_ratio));

	float amplitude_offset = max_amplitude_ / amplitude_limit_ * 255;

	R = std::max(0.0f, std::min(255.0f, R * amplitude_ratio + amplitude_offset));
	G = std::max(0.0f, std::min(255.0f, G * amplitude_ratio + amplitude_offset));
	B = std::max(0.0f, std::min(255.0f, B * amplitude_ratio + amplitude_offset));

}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofSetColor(0, 0, 0);
    //if (loading)
        //ofDrawBitmapString(ofGetHeight());
    ofSetColor(255);
    if (image_.bAllocated()) {
        image_.draw(0, 0);
    }

	float total_width = ofGetWidth();
	// draw the fft resutls:
	ofSetColor(255,255,255,255); // Draw the bands white
	float width = std::min(10.0f, (float)(total_width) / nBandsToGet);
	max_amplitude_ = 0;
	int num_useful_amplitudes = 0;
	prev_average_amplitude_ = average_amplitude_;
	average_amplitude_ = 0;
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		float amplitude = fftSmoothed[i] * 100;
		amplitude = std::min(amplitude, amplitude_limit_);
		ofRect(0+i*width,ofGetHeight()/2-amplitude/2,width,amplitude);
		max_amplitude_ = std::max(max_amplitude_, amplitude);

		if (amplitude> 10.0f) {
			average_amplitude_ += amplitude;
			num_useful_amplitudes++;
		}
	}
	if (num_useful_amplitudes > 0) {
		average_amplitude_ /= num_useful_amplitudes;
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

