#ifndef MVK_TYPES_TYPES_HPP_INCLUDED
#define MVK_TYPES_TYPES_HPP_INCLUDED

#include "types/window.hpp"
#include "utility/verify.hpp"
#include "wrapper/any_wrapper.hpp"

#include <vulkan/vulkan.h>

namespace mvk::validation {
static void destroy_debug_messenger(VkInstance const instance,
                                    VkDebugUtilsMessengerEXT const messenger,
                                    VkAllocationCallbacks const *callback) {
  auto const destroy_debug_utils_messenger =
      reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
          vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

  MVK_VERIFY(destroy_debug_utils_messenger);

  destroy_debug_utils_messenger(instance, messenger, callback);
}
} // namespace mvk::validation

namespace mvk::types {
using device_size = VkDeviceSize;
using queue_index = uint32_t;
using flags = VkFlags;

template <typename Wrapper>
constexpr decltype(auto) get(Wrapper const &wrapper) noexcept {
  return wrapper.get();
}

template <typename Wrapper>
constexpr decltype(auto) get(Wrapper &wrapper) noexcept {
  return wrapper.get();
}

template <typename Wrapper>
constexpr decltype(auto) parent(Wrapper const &wrapper) noexcept {
  return wrapper.deleter().parent();
}

template <typename Wrapper>
constexpr decltype(auto) pool(Wrapper const &wrapper) noexcept {
  return wrapper.deleter().parent();
}

template <typename... Args>
constexpr auto decay(wrapper::any_wrapper<Args...> const &wrapper) noexcept {
  using handle =
      decltype(wrapper::select<wrapper::options::handle>(Args{}...));

  return wrapper::any_wrapper<
      wrapper::options::storage<wrapper::storage::handle_only>,
      wrapper::options::handle<handle>>(get(wrapper));
}

} // namespace mvk::types

namespace mvk::types {
using unique_buffer = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkBuffer>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyBuffer>>;

using buffer = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkBuffer>>;

using unique_pipeline_layout = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkPipelineLayout>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyPipelineLayout>>;

using pipeline_layout = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkPipelineLayout>>;

using unique_command_buffer = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_free>,
    wrapper::options::handle<VkCommandBuffer>,
    wrapper::options::parent<VkDevice>, wrapper::options::pool<VkCommandPool>,
    wrapper::options::deleter_call<vkFreeCommandBuffers>>;

using command_buffer = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkCommandBuffer>>;

using unique_command_pool = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkCommandPool>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyCommandPool>>;

using command_pool = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkCommandPool>>;

using unique_debug_messenger = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkDebugUtilsMessengerEXT>,
    wrapper::options::parent<VkInstance>,
    wrapper::options::deleter_call<validation::destroy_debug_messenger>>;

using unique_descriptor_pool = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkDescriptorPool>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyDescriptorPool>>;

using descriptor_pool = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkDescriptorPool>>;

using unique_descriptor_set_layout = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkDescriptorSetLayout>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyDescriptorSetLayout>>;

using descriptor_set_layout = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkDescriptorSetLayout>>;

using unique_descriptor_set = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_free>,
    wrapper::options::handle<VkDescriptorSet>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::pool<VkDescriptorPool>,
    wrapper::options::deleter_call<vkFreeDescriptorSets>>;

using descriptor_set = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkDescriptorSet>>;

using unique_device_memory = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkDeviceMemory>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkFreeMemory>>;

using device_memory = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkDeviceMemory>>;

using queue = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkQueue>>;

using physical_device = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkPhysicalDevice>>;

using unique_device = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::owner_destroy>,
    wrapper::options::handle<VkDevice>,
    wrapper::options::deleter_call<vkDestroyDevice>>;

using device = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkDevice>>;

using unique_fence = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkFence>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyFence>>;

using fence = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkFence>>;

using unique_framebuffer = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkFramebuffer>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyFramebuffer>>;

using framebuffer = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkFramebuffer>>;

using unique_image_view = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkImageView>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyImageView>>;

using image_view = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkImageView>>;

using unique_instance = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::owner_destroy>,
    wrapper::options::handle<VkInstance>,
    wrapper::options::deleter_call<vkDestroyInstance>>;

using instance = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkInstance>>;

using unique_pipeline = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkPipeline>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyPipeline>>;

using pipeline = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkPipeline>>;

using unique_render_pass = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkRenderPass>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyRenderPass>>;

using render_pass = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkRenderPass>>;

using unique_sampler = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkSampler>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroySampler>>;

using sampler = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkSampler>>;

using unique_semaphore = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkSemaphore>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroySemaphore>>;

using semaphore = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkSemaphore>>;

using unique_surface = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkSurfaceKHR>,
    wrapper::options::parent<VkInstance>,
    wrapper::options::deleter_call<vkDestroySurfaceKHR>>;

using surface = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkSurfaceKHR>>;

using unique_image = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkImage>, wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyImage>>;

using image = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkImage>>;

using unique_shader_module = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkShaderModule>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroyShaderModule>>;

using shader_module = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkShaderModule>>;

using unique_swapchain = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::unique>,
    wrapper::options::deleter<wrapper::deleter::object_destroy>,
    wrapper::options::handle<VkSwapchainKHR>,
    wrapper::options::parent<VkDevice>,
    wrapper::options::deleter_call<vkDestroySwapchainKHR>>;

using swapchain = wrapper::any_wrapper<
    wrapper::options::storage<wrapper::storage::handle_only>,
    wrapper::options::handle<VkSwapchainKHR>>;

[[nodiscard]] types::unique_buffer
create_unique_buffer(types::device device,
                     VkBufferCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_pipeline_layout
create_unique_pipeline_layout(types::device device,
                              VkPipelineLayoutCreateInfo const &info) noexcept;

[[nodiscard]] std::vector<unique_command_buffer>
allocate_unique_command_buffers(
    types::device device, VkCommandBufferAllocateInfo const &info) noexcept;

[[nodiscard]] types::unique_command_pool
create_unique_command_pool(types::device device,
                           VkCommandPoolCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_debug_messenger create_unique_debug_messenger(
    instance const instance,
    VkDebugUtilsMessengerCreateInfoEXT const &info) noexcept;

[[nodiscard]] types::unique_descriptor_pool
create_unique_descriptor_pool(types::device device,
                              VkDescriptorPoolCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_descriptor_set_layout
create_unique_descriptor_set_layout(
    types::device device,
    VkDescriptorSetLayoutCreateInfo const &info) noexcept;

[[nodiscard]] std::vector<unique_descriptor_set>
allocate_unique_descriptor_sets(
    types::device device, VkDescriptorSetAllocateInfo const &info) noexcept;

[[nodiscard]] queue get_queue(types::device device,
                              queue_index index) noexcept;

[[nodiscard]] types::unique_device_memory
create_unique_device_memory(types::device device,
                            VkMemoryAllocateInfo const &info) noexcept;

[[nodiscard]] types::unique_device
create_unique_device(types::physical_device physical_device,
                     VkDeviceCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_fence
create_unique_fence(types::device device,
                    VkFenceCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_framebuffer
create_unique_framebuffer(types::device device,
                          VkFramebufferCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_image_view
create_unique_image_view(types::device device,
                         VkImageViewCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_instance
create_unique_instance(VkInstanceCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_pipeline
create_unique_pipeline(types::device device,
                       VkGraphicsPipelineCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_render_pass
create_unique_render_pass(types::device device,
                          VkRenderPassCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_sampler
create_unique_sampler(types::device device,
                      VkSamplerCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_semaphore
create_unique_semaphore(types::device device,
                        VkSemaphoreCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_image
create_unique_image(types::device device,
                    VkImageCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_shader_module
create_unique_shader_module(types::device device,
                            VkShaderModuleCreateInfo const &info) noexcept;

[[nodiscard]] types::unique_swapchain
create_unique_swapchain(types::device device,
                        VkSwapchainCreateInfoKHR const &info) noexcept;

[[nodiscard]] types::unique_debug_messenger create_unique_debug_messenger(
    instance const instance,
    VkDebugUtilsMessengerCreateInfoEXT const &info) noexcept {
  auto const create_debug_utils_messenger =
      reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
          vkGetInstanceProcAddr(types::get(instance),
                                "vkCreateDebugUtilsMessengerEXT"));

  MVK_VERIFY(create_debug_utils_messenger);

  auto handle = VkDebugUtilsMessengerEXT();
  create_debug_utils_messenger(types::get(instance), &info, nullptr, &handle);
  return types::unique_debug_messenger(handle, types::get(instance));
}
} // namespace mvk::types

#endif
