#ifndef LABEL_CONSTANTS_HPP_
#define LABEL_CONSTANTS_HPP_

// Labels
static const std::string kStartLabel = "start";
static const std::string kLoadLabel = "load";
static const std::string kConfigLabel = "config";
static const std::string kQuitLabel = "quit";

static const std::string kEnvironmentString = "environment";
static const std::string kFloorString = "floor:/n";
static const std::string kLogString = "log";
static const std::string kInventoryString = "inventory";

static const std::string kLevelString = "lvl";
static const std::string kStrString = "str";
static const std::string kDexString = "dex";
static const std::string kConString = "con";
static const std::string kIntString = "int";
static const std::string kHpString = "hp";

// Appendixes
static const std::string kLabelAppendix = "_label";

// Composite Names
static const std::string kStartLabelId = kStartLabel + kLabelAppendix;
static const std::string kLoadLabelId = kLoadLabel + kLabelAppendix;
static const std::string kConfigLabelId = kConfigLabel + kLabelAppendix;
static const std::string kQuitLabelId = kQuitLabel + kLabelAppendix;
static const std::string kFloorLabelId = kLogString + kLabelAppendix;

#endif /* LABEL_CONSTANTS_HPP_ */
