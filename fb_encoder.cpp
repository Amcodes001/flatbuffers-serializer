#include "Client_generated.h"
#include "flatbuffers/flatbuffers.h"
#include <fstream>

int main() {
    // Create a FlatBuffer builder
    flatbuffers::FlatBufferBuilder builder;

    // Create a Person
    auto name = builder.CreateString("Ram");
    auto person = ClientNamespace::CreatePerson(builder, name, 21.0f, 76.5f, ClientNamespace::Gender::Gender_Male);

    // Create a Group with a list of names
    auto group_name = builder.CreateString("FightClub");
    
    std::vector<flatbuffers::Offset<flatbuffers::String>> names;
    names.push_back(builder.CreateString("Ram"));
    names.push_back(builder.CreateString("Shayam"));
    names.push_back(builder.CreateString("Raghuveer"));
    
    auto group = ClientNamespace::CreateGroup(builder, group_name, 24.5f, 66.0f, builder.CreateVector(names));

    // Create a Client union with any one of the types.
    auto client = ClientNamespace::CreateRoot(builder, ClientNamespace::Client_Group, group.Union());
    //auto client = ClientNamespace::CreateRoot(builder, ClientNamespace::Client_Person, person.Union());

    builder.Finish(client);

    // Serialize the data to a binary file
    std::ofstream output_file("fb_bytes.bin", std::ios::binary);
    output_file.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), builder.GetSize());

    return 0;
}
