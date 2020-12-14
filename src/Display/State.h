#pragma once
#include "AssetManager.h"


namespace turbohikerSFML {

    class State {
    public:
        State() = default;
        ~State() = default;

        const std::unique_ptr<AssetManager> &getAssetManager() const;
        void setAssetManager(std::unique_ptr<AssetManager> assetManager);

        virtual void display() = 0;
        virtual void update() = 0;
    private:
        std::unique_ptr<AssetManager> assetManager;

    };

}
