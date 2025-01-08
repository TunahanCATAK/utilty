//
// Created by Tunahan Catak on 13/12/2024.
//

#include <catch2/catch_all.hpp>
#include <string>
#include <vector>

#include "chunk_by.h"
#include "chunk_by_key.h"

struct dog {
    std::string name;
    int age;
};

TEST_CASE("chunk_by_key")
{
    std::vector<dog> dogs{
            {"fido", 12},
            {"bob", 12},
            {"katherine", 9},
            {"max", 12},
            {"sy", 12}
    };

    int group_id = 0;
    int i = 0;
    for (auto&& [key, group] : tc::views::chunk_by_key_view(dogs, [] (auto&& d) { return d.age; })) {
        for (auto&& dog : group)
        {
            switch (i) {
                case 0: REQUIRE(dog.name == "fido"); REQUIRE(group_id == 0); REQUIRE(key == 12); break;
                case 1: REQUIRE(dog.name == "bob"); REQUIRE(group_id == 0); REQUIRE(key == 12); break;
                case 2: REQUIRE(dog.name == "katherine"); REQUIRE(group_id == 1); REQUIRE(key == 9); break;
                case 3: REQUIRE(dog.name == "max"); REQUIRE(group_id == 2); REQUIRE(key == 12); break;
                case 4: REQUIRE(dog.name == "sy"); REQUIRE(group_id == 2); REQUIRE(key == 12); break;
                default : break;
            }
            i++;
        }
        group_id++;
    }
}

TEST_CASE("chunk_by_key pipe")
{
    std::vector<dog> dogs{
            {"fido", 12},
            {"bob", 12},
            {"katherine", 9},
            {"max", 12},
            {"sy", 12}
    };

    int group_id = 0;
    int i = 0;
    for (auto&& [key, group] : dogs | tc::views::views::chunk_by_key([] (auto&& d) { return d.age; })) {
        for (auto&& dog : group)
        {
            switch (i) {
                case 0: REQUIRE(dog.name == "fido"); REQUIRE(group_id == 0); REQUIRE(key == 12); break;
                case 1: REQUIRE(dog.name == "bob"); REQUIRE(group_id == 0); REQUIRE(key == 12); break;
                case 2: REQUIRE(dog.name == "katherine"); REQUIRE(group_id == 1); REQUIRE(key == 9); break;
                case 3: REQUIRE(dog.name == "max"); REQUIRE(group_id == 2); REQUIRE(key == 12); break;
                case 4: REQUIRE(dog.name == "sy"); REQUIRE(group_id == 2); REQUIRE(key == 12); break;
                default : break;
            }
            i++;
        }
        group_id++;
    }
}


TEST_CASE("chunk_by")
{
    std::vector<dog> dogs{
            {"fido", 12},
            {"bob", 12},
            {"katherine", 9},
            {"max", 12},
            {"sy", 12}
    };

    int group_id = 0;
    int i = 0;
    for (auto&& group : tc::views::chunk_by_view(dogs, [] (auto&& left, auto&& right) { return left.age == right.age; })) {
        for (auto&& dog : group)
        {
            switch (i) {
                case 0: REQUIRE(dog.name == "fido"); REQUIRE(group_id == 0); break;
                case 1: REQUIRE(dog.name == "bob"); REQUIRE(group_id == 0); break;
                case 2: REQUIRE(dog.name == "katherine"); REQUIRE(group_id == 1); break;
                case 3: REQUIRE(dog.name == "max"); REQUIRE(group_id == 2); break;
                case 4: REQUIRE(dog.name == "sy"); REQUIRE(group_id == 2); break;
                default : break;
            }
            i++;
        }
        group_id++;
    }

}

TEST_CASE("chunk_by pipie")
{
    std::vector<dog> dogs{
            {"fido", 12},
            {"bob", 12},
            {"katherine", 9},
            {"max", 12},
            {"sy", 12}
    };

    int group_id = 0;
    int i = 0;
    for (auto&& group : dogs | tc::views::views::chunk_by([] (auto&& left, auto&& right) { return left.age == right.age; })) {
        for (auto&& dog : group)
        {
            switch (i) {
                case 0: REQUIRE(dog.name == "fido"); REQUIRE(group_id == 0); break;
                case 1: REQUIRE(dog.name == "bob"); REQUIRE(group_id == 0); break;
                case 2: REQUIRE(dog.name == "katherine"); REQUIRE(group_id == 1); break;
                case 3: REQUIRE(dog.name == "max"); REQUIRE(group_id == 2); break;
                case 4: REQUIRE(dog.name == "sy"); REQUIRE(group_id == 2); break;
                default : break;
            }
            i++;
        }
        group_id++;
    }

}