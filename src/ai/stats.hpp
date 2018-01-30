struct Stats {
    int atk_;
    int def_;
    int max_hp_;
    int current_hp_;
    
    Stats (int atk, int def, int max_hp) :
        atk_ {atk},
        def_ {def},
        max_hp_ {max_hp},
        current_hp_ {max_hp}
    {}
    
};
