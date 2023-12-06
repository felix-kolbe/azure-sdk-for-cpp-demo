#include <iostream>

// Include the necessary SDK headers
#include <azure/core.hpp>
#include <azure/storage/blobs.hpp>

// Add appropriate using namespace directives
using namespace Azure::Storage;
using namespace Azure::Storage::Blobs;

// Secrets should be stored & retrieved from secure locations such as Azure::KeyVault. For
// convenience and brevity of samples, the secrets are retrieved from environment variables.
std::string GetEndpointUrl() { return std::getenv("AZURE_STORAGE_ACCOUNT_URL"); }
std::string GetAccountName() { return std::getenv("AZURE_STORAGE_ACCOUNT_NAME"); }
std::string GetAccountKey() { return std::getenv("AZURE_STORAGE_ACCOUNT_KEY"); }

int main()
{
  std::string endpointUrl = GetEndpointUrl();
  std::string accountName = GetAccountName();
  std::string accountKey = GetAccountKey();

  try
  {
    auto sharedKeyCredential = std::make_shared<StorageSharedKeyCredential>(accountName, accountKey);

    auto blockBlobClient = BlockBlobClient(endpointUrl, sharedKeyCredential);

    // Create some data to upload into the blob.
    std::vector<uint8_t> data = {1, 2, 3, 4};
    Azure::Core::IO::MemoryBodyStream stream(data);

    Azure::Response<Models::UploadBlockBlobResult> response = blockBlobClient.Upload(stream);

    Models::UploadBlockBlobResult model = response.Value;
    std::cout << "Last modified date of uploaded blob: " << model.LastModified.ToString()
              << std::endl;
  }
  catch (const Azure::Core::RequestFailedException& e)
  {
    std::cout << "Status Code: " << static_cast<int>(e.StatusCode)
              << ", Reason Phrase: " << e.ReasonPhrase << std::endl;
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
