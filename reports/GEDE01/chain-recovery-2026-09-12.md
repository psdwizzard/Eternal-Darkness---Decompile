# GEDE01 chain recovery audit — 2026-09-12

## Preserved integration work

- The recovery branch contains commit `cffb6b87f8ec14fda18b5cdadce7b7e99949e685`,
  which adds serialized mirror publication and fail-closed recovery of an old,
  unopened Git index lock. A recovered lock is moved aside rather than deleted.
- The same commit adds three regression cases: recover an old unopened lock,
  reject a recent lock, and reject an old lock held by a live process.
- `checkpoint/foundry-runtime-2026-07-17` at `942afdaea` is an ancestor of the
  recovery branch. `git merge-tree` reports no content conflict. The earlier
  integration failed because the canonical worktree had an uncommitted edit to
  `scripts/decomp-publish-mirror.sh`; Git correctly refused to overwrite it.

## Fresh gate evidence

- `npm ci --ignore-scripts` completed from the locked dependency graph.
- The complete decomp recovery, scheduler, watchdog, review, frontier, envelope,
  and mirror-publisher safety suite passed: 11 files, 76 tests. The monorepo
  TypeScript build also completed successfully.
- `.tools/bin/ninja progress` rebuilt GEDE01 and passed the configured
  `config/GEDE01/build.sha1` check.
- `build/GEDE01/main.dol` hashes to
  `ea24b6af954876ce072562ff39cdb4c81d32be1f` and compares byte-for-byte equal
  to `orig/GEDE01/sys/main.dol`.
- Canonical objdiff: 5,617 of 8,214 functions and 937,948 of 2,300,692 code
  bytes match; 5,852 of 6,898 units are complete.
- Relocation-strict objdiff (`function_reloc_diffs=name_address`): 5,612 of
  8,214 functions and 936,264 of 2,300,692 code bytes match; 5,852 of 6,898
  units are complete.
- The next recorded frontier target remains `fn_802010C8` at `0x802010C8`.

## Remaining operator boundary

This worktree is required to read and modify only its own directory. The
canonical worktree, production publication clone, scheduler database, and user
systemd instance are outside that boundary. Consequently this audit did not
inspect or mutate those resources and does not claim that a production task was
dispatched or published.

Before merging, the owner of the canonical worktree must preserve and commit
its existing edit to `scripts/decomp-publish-mirror.sh` (and the other listed
dirty runtime files), or otherwise reconcile that edit with `cffb6b87f`.
Discarding the canonical edit is not authorized. Once the canonical worktree is
clean, merge this branch and run the normal production scheduler/autopilot. A
successful process launch alone is insufficient: require a real function task,
successful exact-build and objdiff verification, checkpoint integration, and a
public mirror commit carrying that checkpoint's `Source-commit` trailer.
