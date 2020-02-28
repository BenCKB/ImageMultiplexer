#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

typedef std::pair<unsigned int, std::string> Input;

void information() {
	std::cout << "HELP: Image Multiplexer takes as input a pattern to select the channels of the images to later combine, followed by the list of image files. Optionally a output location can be chosen." << std::endl;
	std::cout << std::endl << "Example:" << std::endl << "RRGB inputR.png inputG.png inputB.png inputA.png" << std::endl;
	std::cout << std::endl << "This will take the red channel of inputR.png as the new red channel, the red channel of inputG.png as the new green channel, the green channel of inputB.png as the new blue channel and the blue channel of inputA.png as the new alpha channel." << std::endl;
	std::cout << "Any combination of channels can be chosen. Three channel combinations will only require three input images. Images need to be the same size.";
}

int main(int argc, char* argv[]) {

	std::vector<Input> input;

	//Check input options
	if (argc < 5) { //[name, RGBA, R_image, G_image, B_image]
		std::cout << "Invalid number of input parameters." << std::endl;
		information();
		return EXIT_FAILURE;
	}

	/* === Check Input === */
	std::string pattern = argv[1];

	//Check size of pattern
	if (pattern.size() < 3 || pattern.size() > 4) {
		std::cout << "Invalid number of channels (" << pattern.size() << ") in pattern: " << pattern << std::endl;
		information();
		return EXIT_FAILURE;
	}

	//Collect channel-image combination from input
	for (unsigned int i = 0; i < pattern.size(); ++i) {
		if (i + 2 > argc-1) {
			std::cout << "Not enough images supplied for number of arguments" << std::endl;
			return EXIT_FAILURE;
		}
		//Only allow red/green/blue/alpha channels
		if (pattern[i] == 'R'){
			input.push_back(Input(0, argv[i + 2]));
		}
		else if (pattern[i] == 'G') {
			input.push_back(Input(1, argv[i + 2]));
		}
		else if (pattern[i] == 'B') {
			input.push_back(Input(2, argv[i + 2]));
		}
		else if (pattern[i] == 'A') {
			input.push_back(Input(3, argv[i + 2]));
		}
		else {
			std::cout << "Invalid channel \"" << pattern[i] << "\" in pattern: " << pattern << std::endl;
			information();
			return EXIT_FAILURE;
		}
	}

#ifdef DEBUG
	std::cout << "Detected pattern: " << pattern << std::endl;
	for (Input i : input) {
		std::cout << "Using " << i.first << " channel of " << i.second << std::endl;
	}
#endif

	int width = -1;
	int height = -1;
	int channels = -1;
	
	//Get result image dimensions from first image
	unsigned char* data = stbi_load(input[0].second.c_str(), &width, &height, &channels, 0); // 0 to read channel count, 1..4 to force count. Doesn't change value returned to "channels".

	if (data == NULL) {
		std::cout << "The image " << input[0].second << " couldn't be found or is invalid." << std::endl;
		stbi_image_free(data);
		return EXIT_FAILURE;
	}

#ifdef DEBUG
	std::cout << "Final image specs: (" << width << "w, " << height << "h) with " << channels << " 8-bit channels per pixel." << std::endl;
#endif

	//Reserve memory
	unsigned char* result = new unsigned char[width * 4 * height]; //"height" rows and "width" columns of pixels of "channels" 8-bit components.
	//     0        1        2        3        4        5        6        7
	// RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA
	//     8        9       10       11       12       13       14       15
	// RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA
	// ....

	//Copy values from channel defined in input[i].first to result image
	for (int i = 0; i < input.size(); ++i) {
		data = stbi_load(input[i].second.c_str(), &width, &height, &channels, 0);
		for (int j = 0; j < width * height; ++j) {
			result[i + j * 4] = data[input[i].first + j * channels];
		}
	}

	//Add alpha if input only has three channels
	if (input.size() == 3) {
		for (int j = 0; j < width * height; ++j) {
			result[3 + j * 4] = 255;
		}
	}

	//Write output
	stbi_write_png(".\\result_combined.png", width, height, 4, result, width * 4 * sizeof(char));

	//Free data
	stbi_image_free(data);
	delete[] result;
}