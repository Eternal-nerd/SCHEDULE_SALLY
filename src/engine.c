#include "engine.h"

extern const b8 enable_validation_layers;
extern const char validation_layers[1][100];
extern const char device_extensions[2][100];

/*
-----~~~~~=====<<<<<{_CORE_FUNCTIONS_}>>>>>=====~~~~~-----
*/
b8 run_engine(engine* e) {
	printf("running engine\n");
	
	// init stuff
	if (!init_engine(e)) {
		printf("failed to init engine\n");
		return false;
	}
	
	// main loop
	if (!loop_engine(e)) {
		printf("failed to loop engine\n");
		return false;
	}
	
	// cleanup
	if (!cleanup_engine(e)) {
		printf("failed to cleanup engine\n");
		return false;
	}
	
	return true;
}

b8 init_engine(engine* e) {
	printf("initializing engine\n");
	
	printf("configuring engine\n");
	if (!clear_engine_config(e)) {
		printf("failed to clear engine configuration\n");
		return false;
	}

	if (!config_engine(e)) {
		printf("failed to configure engine\n");
		return false;
	}
	
	printf("initializing SDL\n");
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		printf("failed to initialize SDL\n");
		return false;
	}

    printf("creating SDL window\n");
    e->sdl_window = SDL_CreateWindow(e->config.window_name, e->config.window_width, e->config.window_height, SDL_WINDOW_VULKAN);
    if (!e->sdl_window) {
        printf("failed to create SDL window\n");
		return false;
    }

    printf("setting SDL window to be resizable\n");
    if (!SDL_SetWindowResizable(e->sdl_window, true)) {
        printf("failed to make window resizable\n");
		return false;
    }

	if (!init_vulkan(e)) {
		printf("failed to initialize vulkan\n");
		return false;
	}

	return true;
}

b8 loop_engine(engine* e) {
	printf("executing engine main loop\n");
	
	e->running = true;
	while (e->running) {
		// Poll events (inputs)
		while (SDL_PollEvent(&e->sdl_event)) {
			switch (e->sdl_event.type) {
			// X OUT OF WINDOW
			case SDL_EVENT_QUIT:
				e->running = false;
				break;
			}
        }	
	}
	
	return true;
}

b8 cleanup_engine(engine* e) {
	printf("cleaning up engine\n");
	
	// SDL
    printf("cleaning up SDL\n");
    SDL_DestroyWindow(e->sdl_window);
    SDL_Quit();

	return true;
}

/*
-----~~~~~=====<<<<<{_CONFIGURATION_}>>>>>=====~~~~~-----
*/
b8 clear_engine_config(engine* e) {
	printf("clearing engine config\n");
	
	// clear config
	e->config.window_name = NULL;
	e->config.window_width = 0;
	e->config.window_height = 0;
	e->config.app_name = NULL;
	

	return true;
}

b8 config_engine(engine* e) {
	printf("configuring engine\n");
	
	// FIXME - read from config file
	e->config.window_name = "SCHEDULE_SALLY";
	e->config.window_width = 1100;
	e->config.window_height = 800;
	e->config.app_name = "SCHEDULE_SALLY";
	
	return true;
}

/*
-----~~~~~=====<<<<<{_VULKAN_INIT_}>>>>>=====~~~~~-----
*/
b8 init_vulkan(engine* e) {
	printf("initializing vulkan\n");
	
	// Vulkan instance --------------------====<	
	if (enable_validation_layers && !check_validation_layer_support(validation_layers)) {
        printf("validation layer requested, but not available!\n");
		return false;
    }
	
    VkApplicationInfo appInfo = { 0 };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = e->config.app_name;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Custom";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instanceCreateInfo = { 0 };
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;

	// get extensions
	u32 extension_count = 0;
    const char* const* sdl_extensions = SDL_Vulkan_GetInstanceExtensions(&extension_count);
	
    if (enable_validation_layers) {
        extension_count++; // for debug utils
    }

    char** extensions = NULL;
    extensions = (char**)malloc(extension_count * sizeof(char*));

    if (extensions == NULL) {
        printf("failed to allocate memory for extensions list\n");
        return false;
    }

    if (enable_validation_layers) {
        for (int i = 0; i < extension_count-1; i++) {
            extensions[i] = sdl_extensions[i];
        }
        extensions[extension_count-1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
	}
	else {
        for (int i = 0; i < extension_count; i++) {
            extensions[i] = sdl_extensions[i];
        }
	}

    instanceCreateInfo.enabledExtensionCount = extension_count;
    instanceCreateInfo.ppEnabledExtensionNames = extensions;
	
    
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = populate_debug_messenger_create_info();
    if (enable_validation_layers) {
        instanceCreateInfo.enabledLayerCount = 1; // FIXME HARD CODED
        instanceCreateInfo.ppEnabledLayerNames = validation_layers;
        instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        instanceCreateInfo.enabledLayerCount = 0;
        instanceCreateInfo.pNext = NULL;
    }

    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.pNext = NULL;

	printf("creating vulkan instance\n");
    if (vkCreateInstance(&instanceCreateInfo, NULL, &e->instance) != VK_SUCCESS) {
        printf("failed to create instance!\n");
		return false;
    }

/*
	
    // Vulkan debug layer --------------------====<
    // setup debug messager if in debug mode
    if (enableValidationLayers) {
        printf("setting up debug messenger\n");
        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        util::populateDebugMessengerCreateInfo(createInfo);

        if (util::CreateDebugUtilsMessengerEXT(instance_, &createInfo, nullptr, &debugMessenger_) != VK_SUCCESS) {
            printf("failed to set up debug messenger!\n");
			return false;
        }
    }

    // Vulkan/SDL surface --------------------====<
    printf("creating surface\n");
    if (!SDL_Vulkan_CreateSurface(window_, instance_, nullptr, &surface_)) {
        printf("failed to create SDL window surface!\n");
    }
    
    // TODO: print device selected to logger!!!!
    // Vulkan physical device (GPU) --------------------====<
    printf("selecting physical device\n");
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance_, &deviceCount, nullptr);

    if (deviceCount == 0) {
        printf("failed to find GPUs with Vulkan support!\n");
		return false;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance_, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (util::isDeviceSuitable(device, surface_, deviceExtensions)) {
            physicalDevice_ = device;
            break;
        }
    }

    if (physicalDevice_ == VK_NULL_HANDLE) {
        printf("failed to find a suitable GPU!\n");
		return false;
    }

    // Vulkan LOGICAL Device --------------------====<
    printf("creating logical device\n");
    QueueFamilyIndices indices = util::findQueueFamilies(physicalDevice_, surface_);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { 
        indices.graphicsFamily.value(),
        indices.presentFamily.value() 
    };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    printf("checking vulkan device features\n");
    VkPhysicalDeviceExtendedDynamicState3FeaturesEXT dynamicState3Features = {};
    dynamicState3Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT;

    VkPhysicalDeviceVulkan12Features vulkan12Features = {};
    vulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    vulkan12Features.pNext = &dynamicState3Features;

    VkPhysicalDeviceFeatures2 physicalFeatures2 = {};
    physicalFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    physicalFeatures2.pNext = &vulkan12Features;

    vkGetPhysicalDeviceFeatures2(physicalDevice_, &physicalFeatures2);

    // Logic if feature is not supported
    if (vulkan12Features.runtimeDescriptorArray && vulkan12Features.shaderSampledImageArrayNonUniformIndexing && dynamicState3Features.extendedDynamicState3PolygonMode == VK_FALSE) {
        printf("needed features not enabled on chosen device\n");
		return false;
    }


    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();

    deviceCreateInfo.pNext = &physicalFeatures2;
    deviceCreateInfo.pEnabledFeatures = NULL;

    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers) {
        deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else {
        deviceCreateInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice_, &deviceCreateInfo, nullptr, &device_) != VK_SUCCESS) {
        printf("failed to create logical device!\n");
		return false;
    }

    printf("getting device queues\n");
    vkGetDeviceQueue(device_, indices.graphicsFamily.value(), 0, &graphicsQueue_);
    vkGetDeviceQueue(device_, indices.presentFamily.value(), 0, &presentQueue_);
*/

    // Free memory for the array of pointers
    free(extensions);

	return true;
}