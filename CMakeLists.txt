cmake_minimum_required(VERSION 3.13)

project(azure-sdk-for-cpp-demo LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    azuresdk
    GIT_REPOSITORY      https://github.com/Azure/azure-sdk-for-cpp.git
    GIT_TAG             main
)
FetchContent_GetProperties(azuresdk)
if(NOT azuresdk_POPULATED)
    FetchContent_Populate(azuresdk)
    # Adding all Azure SDK libraries
    add_subdirectory(${azuresdk_SOURCE_DIR} ${azuresdk_BINARY_DIR} EXCLUDE_FROM_ALL)

    # Adding one Azure SDK Library only (Storage blobs)
    # add_subdirectory(${azuresdk_SOURCE_DIR}/sdk/storage/azure-storage-blobs ${azuresdk_BINARY_DIR} EXCLUDE_FROM_ALL)

    # Adding sub components in their own binary dirs
    # add_subdirectory(${azuresdk_SOURCE_DIR}/sdk/core/azure-core ${azuresdk_BINARY_DIR}/azure-core EXCLUDE_FROM_ALL)
    # add_subdirectory(${azuresdk_SOURCE_DIR}/sdk/storage/azure-storage-common ${azuresdk_BINARY_DIR}/azure-storage-common EXCLUDE_FROM_ALL)
    # add_subdirectory(${azuresdk_SOURCE_DIR}/sdk/storage/azure-storage-blobs ${azuresdk_BINARY_DIR}/azure-storage-blobs EXCLUDE_FROM_ALL)

    # Adding the upper level components
    # add_subdirectory(${azuresdk_SOURCE_DIR}/sdk/core EXCLUDE_FROM_ALL)
    # add_subdirectory(${azuresdk_SOURCE_DIR}/sdk/storage EXCLUDE_FROM_ALL)
endif()

add_executable(${PROJECT_NAME} sample.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Azure::azure-storage)
# target_link_libraries(${PROJECT_NAME} PRIVATE Azure::azure-identity)
