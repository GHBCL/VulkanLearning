#pragma once
#include <array>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "vulkan/vulkan.h"

namespace my_vulkan
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec2 texCoord;
		glm::vec3 normal;

		static VkVertexInputBindingDescription getBindingDescription()
		{
			VkVertexInputBindingDescription bindingDescription{};

			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX; //Move to the next data entry after each vertex

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
			attributeDescriptions[0].binding = 0; //tells vulkan which binding the per-vertex data comes
			attributeDescriptions[0].location = 0; //the param references the location directive of the input in the vertex shader. The input in the vertex shader with location 0 is the position,
			//which has two 32-bit float components
			attributeDescriptions[0].format = VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, texCoord);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, normal);

			return attributeDescriptions;
		}

		bool operator==(const Vertex& other) const {
			return pos == other.pos && texCoord == other.texCoord && normal == other.normal;
		}
	};
}

namespace std
{
	template<> struct hash<my_vulkan::Vertex>
	{
		size_t operator()(my_vulkan::Vertex const& vertex) const
		{
			size_t hashValue = 0;

			// Hash each component using the std::hash function
			hashValue ^= std::hash<glm::vec3>()(vertex.pos);
			hashValue ^= std::hash<glm::vec3>()(vertex.normal);
			hashValue ^= std::hash<glm::vec2>()(vertex.texCoord);

			return hashValue;
		}
	};
}

