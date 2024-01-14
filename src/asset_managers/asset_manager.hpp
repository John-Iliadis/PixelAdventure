//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_ASSET_MANAGER_HPP
#define PLATFORMER_ASSET_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <stdexcept>


template <typename Derived, typename asset_type>
class AssetManager
{
public:
    AssetManager() = default;
    virtual ~AssetManager() = default;

    asset_type& get(const std::string& key);
    const asset_type& get(const std::string& key) const;

    void load(const std::string& key, const std::string& file_name);
    void load_directory(const std::string& dir);

    void remove(const std::string& key);

private:
    std::unordered_map<std::string, std::unique_ptr<asset_type>> map;
};

#include "asset_manager.inl"


#endif //PLATFORMER_ASSET_MANAGER_HPP
