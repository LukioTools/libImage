#include <iostream>
#include <string>
#include <jpeglib.h>


std::string filename = "img.jpg";



#define slog(var) std::clog << #var": " <<  var << std::endl;

void error_exit(j_common_ptr cinfo) {
    char buffer[JMSG_LENGTH_MAX];
    (*cinfo->err->format_message)(cinfo, buffer);
    fprintf(stderr, "JPEG Error: %s\n", buffer);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr jerr;

    // Initialize the JPEG decompression object
    cinfo.err = jpeg_std_error(&jerr);
    jerr.error_exit = error_exit;

    jpeg_create_decompress(&cinfo);

    // Specify the input file
    FILE *infile = fopen(filename.c_str(), "rb");
    if (!infile) {
        fprintf(stderr, "Error opening JPEG file.\n");
        exit(EXIT_FAILURE);
    }

    // Specify the source of the compressed data
    jpeg_stdio_src(&cinfo, infile);

    // Read file parameters and start decompression
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);

    // Allocate memory for the image data
    JSAMPARRAY buffer;
    int row_stride;
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = cinfo.mem->alloc_sarray((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

    // Loop through the image and read the data line by line
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        // Process the image data as needed
        // 'buffer' contains the pixel values of the current line
    }

    // Finish decompression
    (void) jpeg_finish_decompress(&cinfo);
    fclose(infile);

    // Clean up and release resources
    jpeg_destroy_decompress(&cinfo);
        
    std::cout << (int) buffer[0][0] << " / " << (int) buffer[0][1] << " / " << (int) buffer[0][2] << std::endl;

    

    return 0;
}
