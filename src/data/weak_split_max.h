// Hardcoded list of species eligible for the Tech House secondary attacking IV service.

// The code assumes that a Pokemon will only be in one of these lists since it's intended to deal with the weaker attacking stat.
//But in the event of overlap, attack would be used based on ordering.
static const u16 sWeakSplitMaxAttackSpecies[] =
{
    SPECIES_ALAKAZAM,
    SPECIES_RILLABOOM,
    SPECIES_GENGAR,
    SPECIES_BEHEEYEM,
    SPECIES_REUNICLUS,
    SPECIES_BUTTERFREE,
};

static const u16 sWeakSplitMaxSpAttackSpecies[] =
{
    SPECIES_GYARADOS,
    SPECIES_RAMPARDOS,
    SPECIES_FEAROW,
    SPECIES_DODRIO,
    SPECIES_MACHAMP,
};
