# NPC and trainer development notes


## Trainer identity and route bosses

A route boss with prerequisites, consent, or rewards uses `TRAINER_TYPE_NONE` so its script controls entry into battle. `IsRouteBossTrainer` supplies the full pre-battle heal. Prerequisites include the actual defeat flags for the relevant trainers.

In Restricted Mode,  Route Bosses often cannot be battled after a certain progression point.

## Party design

`trainerproc` leaves an unspecified Pokemon gender at zero. The shared trainer generator retains the previous defaults: personality low byte `0x88` for a male trainer in singles, `0x78` for a female trainer in singles, and `0x80` for other battle types. Explicit Pokemon genders override these values; partners retain random unspecified genders. Keep this contract when updating the generator API.

When trying to figure out the right Pokemon to use for a trainer, their existing intro, defeat, and post-battle dialogue is helpful. The NPC's location and trainer class also is a big factor.


 The diversity report is refreshed with:
```sh
python3 tools/elastic_emerald_helpers/analyze_trainer_types.py
```

This script is helpful to figure out what types should get more representation that fit the given trainers.  For otherwise suitable candidates, my preference is an unused species, then an unused ability on a used species, then a repeated species/ability pairing when it makes sense for theme or battle design. 


## Scaling and rewards

Runtime level scaling lives in `GetTrainerLevelModifier(trainerNum)` and is applied when trainer Pokémon are created, capped at `MAX_LEVEL`. This avoids duplicate parties solely for level changes. Base/rematch IDs and route-boss membership determine the affected group; independent progression flags can  cumulative bonuses. I record those triggers ancontributed totals in `docs/gameplay/trainers.md`.


## Documentation and review

My trainer notes cover prerequisites, mode cutoffs, rewards, scaling, reused slots, and healing. Parties inside `trainer-party` markers are synchronized by:

```sh
python3 tools/elastic_emerald_helpers/sync_trainer_docs.py
python3 tools/elastic_emerald_helpers/sync_trainer_docs.py --check
```

