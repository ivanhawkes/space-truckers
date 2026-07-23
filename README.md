# Concept

A simple space trading game in the style of the original Elite.

## NOTES:

Process the individual YAML files into a single file.

```bash
cd Content/Data

# Concatenate all the YAML files and explode the anchor references.
# You need to use this method because the references are to anchors that are
# in separate files, and YQ doesn't like that.
# TODO: Find a cleaner way around this.
clear && find *.yaml | sort | xargs  -d '\n' cat | yq --yaml-fix-merge-anchor-to-spec=true e 'explode(.)' > generated/combined.yaml

# Combine the single YAML files into one large one.
yq -n --yaml-fix-merge-anchor-to-spec=true 'load("item-categories.yaml") * load("items.yaml") * load("item-listings.yaml")' > combined.yaml

# Parse the output file and 'explode' it so the anchors and references are flat values.
yq 'explode(.)' combined.yaml

# Do both.
yq -n --yaml-fix-merge-anchor-to-spec=true 'load("item-categories.yaml") * load("items.yaml") * load("item-listings.yaml")' | yq 'explode(.)'

```

# Project Management

```bash
cd website
hugo new content kanban/acceptance/ac-001-test.md --kind acceptance
hugo new content kanban/bugs/bg-001-test.md --kind bugs
hugo new content kanban/deliverables/dl-001-test.md --kind deliverables
hugo new content kanban/deployment/dl-001-test.md --kind deployment
hugo new content kanban/epics/ep-001-test.md --kind epics
hugo new content kanban/features/ft-001-test.md --kind features
hugo new content kanban/ideation/id-001-test.md --kind ideation
hugo new content kanban/meta/mt-001-test.md --kind meta
hugo new content kanban/releases/rl-001-test.md --kind releases
hugo new content kanban/requests/rq-001-test.md --kind requests
hugo new content kanban/scaffold/sf-001-test.md --kind scaffold
hugo new content kanban/specifications/sp-001-test.md --kind specifications
hugo new content kanban/testing/ts-001-test.md --kind testing
hugo new content kanban/user-stories/us-001-test.md --kind user-stories
```