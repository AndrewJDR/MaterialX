#ifndef MATERIALX_IMAGEHANDLER_H
#define MATERIALX_IMAGEHANDLER_H

#include <string>
#include <memory>

namespace MaterialX
{
/// Shared pointer to an ImageHandler
using ImageHandlerPtr = std::shared_ptr<class ImageHandler>;

/// @class @ImageHandler
/// Abstract class representing an disk image handler
///
class ImageHandler
{
public:
    /// Default constructor
    ImageHandler() {}
    
    /// Default destructor
    virtual ~ImageHandler() {}

    /// Save image to disk. This method must be implemented by derived classes.
    /// @param fileName Name of file to save image to
    /// @param width Width of image in pixels
    /// @param height Height of image in pixels
    /// @param channelCount Number of channels per pixel
    /// @param buffer Floating point buffer of pixels.
    virtual bool saveImage(const std::string& fileName,
                            unsigned int width,
                            unsigned int height,
                            unsigned int channelCount,
                            const float* buffer) = 0;

    /// Load an image from disk. This method must be implemented by derived classes.
    /// @param fileName Name of file to load image from
    /// @param width Width of image in pixels
    /// @param height Height of image in pixels
    /// @param channelCount Number of channels per pixel
    /// @param buffer Floating point buffer of pixels.
    virtual bool loadImage(const std::string& fileName,
                            unsigned int& width,
                            unsigned int& height,
                            unsigned int& channelCount,
                            float** buffer) = 0;
};

} // namespace MaterialX
#endif
