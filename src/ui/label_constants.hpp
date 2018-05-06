#ifndef LABEL_CONSTANTS_HPP_
#define LABEL_CONSTANTS_HPP_

// Labels
static const std::string kStartLabel = "start";
static const std::string kLoadLabel = "load";
static const std::string kConfigLabel = "config";
static const std::string kQuitLabel = "quit";

// Appendixes
static const std::string kLabelAppendix = "_label";

// Composite Names
static const std::string kStartLabelId = kStartLabel + kLabelAppendix;
static const std::string kLoadLabelId = kLoadLabel + kLabelAppendix;
static const std::string kConfigLabelId = kConfigLabel + kLabelAppendix;
static const std::string kQuitLabelId = kQuitLabel + kLabelAppendix;

#endif /* LABEL_CONSTANTS_HPP_ */
