#pragma once

#include "messages/lazyloadedimage.hpp"

#include <map>
#include <memory>
#include <mutex>

namespace chatterino {

class EmoteManager;
class WindowManager;

class Resources
{
    EmoteManager &emoteManager;
    WindowManager &windowManager;

public:
    explicit Resources(EmoteManager &emoteManager, WindowManager &windowManager);

    messages::LazyLoadedImage *badgeStaff;
    messages::LazyLoadedImage *badgeAdmin;
    messages::LazyLoadedImage *badgeGlobalModerator;
    messages::LazyLoadedImage *badgeModerator;
    messages::LazyLoadedImage *badgeTurbo;
    messages::LazyLoadedImage *badgeBroadcaster;
    messages::LazyLoadedImage *badgePremium;
    messages::LazyLoadedImage *badgeVerified;

    messages::LazyLoadedImage *cheerBadge100000;
    messages::LazyLoadedImage *cheerBadge10000;
    messages::LazyLoadedImage *cheerBadge5000;
    messages::LazyLoadedImage *cheerBadge1000;
    messages::LazyLoadedImage *cheerBadge100;
    messages::LazyLoadedImage *cheerBadge1;

    std::map<std::string, messages::LazyLoadedImage *> cheerBadges;

    struct BadgeVersion {
        BadgeVersion() = delete;

        explicit BadgeVersion(QJsonObject &&root, EmoteManager &emoteManager,
                              WindowManager &windowManager);

        messages::LazyLoadedImage *badgeImage1x;
        messages::LazyLoadedImage *badgeImage2x;
        messages::LazyLoadedImage *badgeImage4x;
        std::string description;
        std::string title;
        std::string clickAction;
        std::string clickURL;
    };

    struct BadgeSet {
        std::map<std::string, BadgeVersion> versions;
    };

    std::map<std::string, BadgeSet> badgeSets;

    bool dynamicBadgesLoaded = false;

    messages::LazyLoadedImage *buttonBan;
    messages::LazyLoadedImage *buttonTimeout;

    struct Channel {
        std::map<std::string, BadgeSet> badgeSets;

        bool loaded = false;
    };

    //       channelId
    std::map<std::string, Channel> channels;

    // Chatterino badges
    struct ChatterinoBadge {
        ChatterinoBadge(const std::string &_tooltip, messages::LazyLoadedImage *_image)
            : tooltip(_tooltip)
            , image(_image)
        {
        }

        std::string tooltip;
        messages::LazyLoadedImage *image;
    };

    //       username
    std::map<std::string, std::shared_ptr<ChatterinoBadge>> chatterinoBadges;

    void loadChannelData(const std::string &roomID, bool bypassCache = false);
    void loadChatterinoBadges();
};

}  // namespace chatterino
