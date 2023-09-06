#include "Client_generated.h"
#include "flatbuffers/flatbuffers.h"
#include <fstream>
#include <iostream>

void PrintPerson(const ClientNamespace::Person* person) {
    std::cout << "Name: " << person->name()->c_str() << std::endl;
    std::cout << "Age: " << person->age() << std::endl;
    std::cout << "Weight: " << person->weight() << std::endl;
    std::cout << "Gender: " << (person->gender() == ClientNamespace::Gender_Male ? "Male" : "Female") << std::endl;
}

void PrintGroup(const ClientNamespace::Group* group) {
    std::cout << "Group Name: " << group->groupname()->c_str() << std::endl;
    std::cout << "Average Age: " << group->averageage() << std::endl;
    std::cout << "Average Weight: " << group->averageweight() << std::endl;
    std::cout << "Names:" << std::endl;
    for (size_t i = 0; i < group->names()->size(); ++i) {
        std::cout << "  " << group->names()->Get(i)->c_str() << std::endl;
    }
}

int main() {
    // Read the binary file into a buffer
    std::ifstream input_file("fb_bytes.bin", std::ios::binary | std::ios::ate);
    if (!input_file.is_open()) {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        return 1;
    }

    std::ifstream::pos_type file_size = input_file.tellg();
    
    std::vector<char> buffer(file_size);
    input_file.seekg(0, std::ios::beg);
    input_file.read(buffer.data(), file_size);
    input_file.close();

    // Deserialize the data
    flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t*>(buffer.data()), file_size);
    if (!ClientNamespace::VerifyRootBuffer(verifier)) {
        std::cerr << "Error: Invalid Client buffer." << std::endl;
        return 1;
    }

    auto client = ClientNamespace::GetRoot(buffer.data());

    // Determine if it's a Person or Group and print accordingly
    if (client->client_type() == ClientNamespace::Client_Person) {
        PrintPerson(client->client_as_Person());
    } 
    else if (client->client_type() == ClientNamespace::Client_Group) {
        PrintGroup(client->client_as_Group());
    }

    return 0;
}
