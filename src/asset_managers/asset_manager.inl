template<typename Derived, typename asset_type>
asset_type& AssetManager<Derived, asset_type>::get(const std::string &key)
{
    if (auto it = map.find(key);
            it != map.end())
    {
        return *(it->second);
    }
    else
    {
        throw std::runtime_error("AssetManager::get - Asset " + key +  " missing from map\n");
    }
}

template<typename Derived, typename asset_type>
const asset_type& AssetManager<Derived, asset_type>::get(const std::string& key) const
{
    if (auto it = map.find(key);
            it != map.end())
    {
        return *(it->second);
    }
    else
    {
        throw std::runtime_error("AssetManager::get - Asset " + key +  " missing from map\n");
    }
}

template<typename Derived, typename asset_type>
void AssetManager<Derived, asset_type>::load(const std::string &key, const std::string &file_name)
{
    std::unique_ptr<asset_type> asset = static_cast<Derived*>(this)->load(file_name);

    auto result = map.insert(std::make_pair(key, std::move(asset)));

    if (!result.second)
    {
        throw std::runtime_error("AssetManager<Derived, asset_type>::load - Failed to insert " + file_name + " to map\n");
    }
}

template<typename Derived, typename asset_type>
void AssetManager<Derived, asset_type>::load_directory(const std::string &dir)
{
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (fs::is_directory(entry))
        {
            load_directory(entry.path().string());
        }
        else if (fs::is_regular_file(entry))
        {
            if (entry.path().extension().string() == ".txt") continue;

            std::string key = entry.path().stem().string();
            std::string file_path = entry.path().string();

            load(key, file_path);
        }
    }
}

template <typename Derived, typename asset_type>
void AssetManager<Derived, asset_type>::load_directory_list(const std::string& file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
        throw std::runtime_error("AssetManager::load_from_list - Failed to open file " + file_name);

    nlohmann::json directory_list = nlohmann::json::parse(file);

    for (const std::string& dir : directory_list)
        load_directory(dir);
}

template<typename Derived, typename asset_type>
void AssetManager<Derived, asset_type>::remove(const std::string &key)
{
    if (auto result = map.erase(key);
        result != 1)
    {
        throw std::runtime_error("AssetManager<Derived, asset_type>::remove - Failed to remove " + key + " from map\n");
    }
}
