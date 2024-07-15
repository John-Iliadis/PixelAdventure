//
// Created by Gianni on 14/07/2024.
//

#ifndef PIXEL_ADVENTURE_PARALLEL_TASK_HPP
#define PIXEL_ADVENTURE_PARALLEL_TASK_HPP

#include "world.hpp"
#include "../states/game_context.hpp"
#include "../enums/state_identifiers.hpp"
#include "../asset_managers/texture_manager.hpp"
#include "../asset_managers/font_manager.hpp"
#include "../asset_managers/music_manager.hpp"
#include "../asset_managers/sound_buffer_manager.hpp"


class ParallelTask
{
public:
    ParallelTask(StateID next_state)
        : m_next_state(next_state)
    {
    }

    virtual ~ParallelTask() = default;

    virtual void execute() = 0;
    virtual bool has_output() = 0;
    virtual void* get_output() = 0;

public:
    StateID m_next_state;
};


class DoNothing : public ParallelTask
{
public:
    DoNothing(StateID next_state)
        : ParallelTask(next_state)
    {
    }

    void execute() override { }
    bool has_output() override { return false; }
    void* get_output() override { return nullptr; }
};


class LoadWorld : public ParallelTask
{
public:
    LoadWorld(const GameContext& context, StateID next_state)
        : ParallelTask(next_state)
        , m_context(context)
        , m_world(nullptr)
    {
    }

    void execute() override { m_world = new World(m_context); }
    bool has_output() override { return true; }
    void* get_output() override { return m_world; }

private:
    GameContext m_context;
    World* m_world;
};


class LoadAssets : public ParallelTask
{
public:
    LoadAssets(const GameContext& context, StateID next_state)
        : ParallelTask(next_state)
        , m_context(context)
    {
    }

    void execute() override
    {
        m_context.texture_manager->load_directory("../assets/textures");
        m_context.sound_buffer_manager->load_directory("../assets/sounds");
        m_context.music_manager->load_directory("../assets/music");
        m_context.settings->load_from_file("../data/settings/settings.json");
    }

    bool has_output() override { return false; }
    void* get_output() override { return nullptr; }

private:
    GameContext m_context;
};


#endif //PIXEL_ADVENTURE_PARALLEL_TASK_HPP
