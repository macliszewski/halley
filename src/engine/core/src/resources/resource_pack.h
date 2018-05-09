#pragma once

#include "resources/resource_locator.h"
#include "resources/asset_database.h"

namespace Halley {
	class SystemAPI;

	class PackResourceLocator : public IResourceLocatorProvider {
	public:
		PackResourceLocator(SystemAPI& system, const Path& filePath, const String& encryptionKey = "", bool preLoad = false);

	protected:
		std::unique_ptr<ResourceData> getData(const String& asset, AssetType type, bool stream) override;
		const AssetDatabase& getAssetDatabase() const override;

		SystemAPI& system;
		std::unique_ptr<AssetDatabase> assetDb;
	};
}