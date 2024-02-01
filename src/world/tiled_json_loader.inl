namespace TiledJsonLoader
{
    template <typename T>
    T get_property(const nlohmann::json& property_array, const std::string& property_name)
    {
        auto itr = std::find_if(property_array.begin(), property_array.end(),
                             [&property_name] (const nlohmann::json& property_object) {
           return (property_object["name"].get<std::string>() == property_name);
        });

        assert(itr != property_array.end());

        return (*itr)["value"].template get<T>();
    }
}
