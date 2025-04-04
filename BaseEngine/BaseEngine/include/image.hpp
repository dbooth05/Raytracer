#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include "vulkan/vulkan.h"

namespace BaseEngine {
    enum class ImageFormat {
        NONE = 0,
        RGBA,
        RGBA32F
    };

    class Image {
        public:
            Image(std::string_view path);
            Image(uint32_t wd, uint32_t ht, ImageFormat format, const void* data = nullptr);

            ~Image();

            void setData(const void* data);
            VkDescriptorSet getDescriptorSet() const { return m_DescriptorSet; }

            void resize(uint32_t wd, uint32_t ht);

            uint32_t getWd() const { return m_Wd; }
            uint32_t getHt() const { return m_Ht; }

        private:
            void allocateMemory(uint64_t size);
            void release();

        private:
            uint32_t m_Wd = 0, m_Ht = 0;

            VkImage m_Image = nullptr;
            VkImageView m_ImageView = nullptr;
            VkDeviceMemory m_Memory = nullptr;
            VkSampler m_Sampler = nullptr;

            ImageFormat m_Format = ImageFormat::NONE;

            VkBuffer m_StagingBuf = nullptr;
            VkDeviceMemory m_StagingBufMem = nullptr;

            size_t m_AlignedSize = 0;

            VkDescriptorSet m_DescriptorSet = nullptr;

            std::string m_Filepath;
    };
}

#endif
