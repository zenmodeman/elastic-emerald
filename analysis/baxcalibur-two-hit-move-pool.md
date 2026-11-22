# Mega Baxcalibur two-hit matchup pool

Reviewed against `e2d2149d38` and the local generated learnsets on 2026-11-19. These are level-50 singles calculations for specified switch-in moves. They cover the ordinary Glaive Rush or Icicle Crash follow-up lines, with no Tera, field effects, or prior damage. The screening calculator does not predict AI move choices or run the ROM.

## Opponent move candidates

| Category | Moves to consider |
| --- | --- |
| Physical coverage | Stone Edge, Cross Chop, Sacred Sword, Earthquake, High Horsepower, Dragon Claw, Leaf Blade, Seed Bomb, X-Scissor, Megahorn, Ice Spinner, Throat Chop, Aqua Tail, Crabhammer, Spectral Thief |
| Physical moves with additional conditions | Drain Punch and Leech Life can heal the opponent before Bax acts if it has already taken item damage. Poltergeist requires a held item. Poison Jab needs a residual damage check. Giga Impact can be a follow-up because the opponent has no later action in the line. |
| Special coverage | Aura Sphere, Dragon Pulse, Power Gem, Dazzling Gleam, Hyper Voice, Surf, Scald, Hydro Pump, Flamethrower, Heat Wave, Fire Blast |
| Special moves with additional conditions | Giga Drain has the same healing consideration as Drain Punch. Grass Knot reaches 120 power against both Baxcalibur forms. Bleakwind Storm can be considered in Ice Shard lines, since its Speed drop would compromise the Bulldoze speed check. |
| Electric pivot | Thunderbolt with Sheer Force. Check both the power boost and the suppression of paralysis. |

On the chosen pivot, check any persistent effect that could change the next turn. Exclude action denial, including flinches and paralysis, and moves with Attack, Defense, or Sp. Def drops. Check that every move on the proposed opponent set is safe on the turn Bax Mega Evolves. For Bulldoze, ensure Bax still moves first on the finishing turn against each viable opponent action, including Speed effects and priority. Trace damage-changing abilities and consumable items separately. A conditional effect or an ability can change which attack is optimal.

## Bait examples for the checked cases

| Opponent | Example Pokémon to bait the pivot move |
| --- | --- |
| Pinsir | Levitate Mismagius for Throat Chop |
| Mega Gallade, already evolved | Gastrodon for Leaf Blade |
| Marshadow | Farigiraf for Throat Chop |
| Annihilape | Gastrodon for Seed Bomb |
| Excadrill | Air Balloon Kingambit for X-Scissor |
| Great Tusk | Gliscor for Ice Spinner |
| Blastoise | Rhyperior for Surf |
| Victini or Zeraora | Rhyperior for Grass Knot |

The [case calculator](../tools/elastic_emerald_helpers/analyze_baxcalibur_capped_matchups.py) prints the selected EV spreads, maximum incoming crit rolls, minimum outgoing rolls and base-form margins. For physical cases, the base comparison grants favorable item assumptions and omits opposing Leftovers from the required damage as an upper bound. For the special cases, it checks Assault Vest and shows one damage-item alternative. Where the opponent holds Sitrus Berry, it evaluates every first-hit roll before deciding whether the berry activates.

Icicle Crash is a level-62 move on the current Baxcalibur level-up list. The Crash rows assume it is already available on the level-50 battler, such as after level scaling.
