#include "State.h"




namespace turbohikerSFML {

    const std::unique_ptr<AssetManager> &turbohikerSFML::State::getAssetManager() const {
        return assetManager;
    }

    void turbohikerSFML::State::setAssetManager(std::unique_ptr<AssetManager> _assetManager) {
        assetManager = std::move(_assetManager);
    }

}