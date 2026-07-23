---
author: Ivan Hawkes
categories:
  - Documentation
  - Concept
  - Idea
date: '2026-05-07'
description:
  A document that briefly describes the goals and intents of this project.
title: Ideation
type: specification
---

# Space Truckers

Space Truckers is an SDK for Space Trading Games.

## Purpose

The purpose of this document is to state quite clearly the idea that will be
further developed into a project.

## Logline

Describe in a single sentence the purpose of this project.

> I wish to create an SDK that can be used for space trading simulations.

## Progress

{{< kanban-list-short prefix=id  >}}

## Expand the Idea

Take each key idea and move it into a section with a heading. Take all the small
related ideas and move them under that heading.

Break the ideas into major and minor features. State each feature clearly and
concisely.

Make a new feature Kanban for each major feature.

## TODO

### Generate the map

	* populate it with star systems
	* decide resource scarcity for each
	* set market prices
	* simulate govenment, natural disasters, resource mining operations, etc

## Markets

	* bonds / ZC bonds
	* stocks / equities
	* options
	* futures
	* indices
	* ETF (Exchange Traded Funds)
	* commodities

## Ships

	* base ships
	* extend with guns, better drives, improved AI, longer range communications
	* robots for unloading

## Trade Hubs

Since it's costly to enter a gravity well of any decent size most trading will
be done with orbital platforms, captive
asteroids, wrecks of massive ships, etc.

Each trade hub will have one or more markets, probably just the one to simplify
the game code a bit.

## Trade Parameters

You can go fast, or you can go cheap, but you can't do both. Fuel burns at the
start and end of journeys will need to be factored into the price of goods.

Ships that are unmanned are preferred since this allows them to accelerate for
long periods at multiples of gravity
without killing the people in them. Slave ships are an obvious exception to this
and will account for some part of the
very high price of slaves.

Random encounters by pirates and space debris might cause shifts in the markets
due to shortages of goods.

Supply and demand will play a part in market rates.

Planets might be better suited to organic materials than space stations.

There is no such thing as artificial gravity or faster than light travel. Single
exception is the quantum entangled bits
that form a part of their galactic wide internet. A new receiver has to be
delivered to the region the slow way first in
order to achieve this faster than light transmission of information. Bandwidth
is limited and costly.

## Tech Tree Advancement

Each community will have its own level of tech advancement based on it's
resources available,
population (skills, health, etc), and past achievements.

They will need to trade for materials / tech that can help advance them through
a tech tree.

NOTE: each period builds on previous periods. Some goods will drop in value at
the start of the next period, others are evergreen and persist for the rest of
the tree. By
default,
anything they make is also considered available for sale.

Rough plan:

### stone age

    - Discover
        - religion
        - fire
    - Social Change
        - domesticated dogs
        - slavery
        - cave art
    - Make / Invent
        - charcoal
        - glue
        - rope
        - stone tools
    - Supply
        - slaves
        - pigments
        - pottery
        - natural drugs
        - precursors for biotech weapons i.e. novel viruses
        - hides
        - furs

### pre-history

    - Discover
        - fermentation
        - agriculture
        - irrigation
    - Social Change
        - mining
    - Make / Invent
        - flour
        - bread
        - beer
        - wine
        - domesticated grains
        - domesticated animals
        - mud bricks
        - lime
        - lead
        - ard plough
    - Supply
        - alcohol

### copper age

    - Discover
        - sailing (exploration)
    - Social Change
        - salt mining
    - Make / Invent
        - crucible
        - fired bricks
        - natron
        - plumbing
        - mirrors
    - Supply

### bronze age - much the same as above

    - Discover
        - wheel
    - Social Change
    - Make / Invent
        - furnace
        - tin
        - bronze
        - brass
    - Supply
        - metals
        - minerals
        - jewelery
        - cloth / clothing
        - mercenaries

### iron age

    - Discover
        - early farming implements
    - Social Change
        - rise of the kings
    - Make / Invent
        - carts drawn by animals
        - latrines
        - swords
        - writing
        - vinegar
        - shaduf
    - Supply
        - harder metals

### classical age

    - Discover
        - alchemy
        - distillation
        - maths
    - Social Change
        - theatre
        - world conquest
    - Make / Invent
        - shipping
        - water clock
        - star charts
        - Antikythera mechanism / analogue computer
        - orary
        - ceramics
        - mills
        - siege weapons
        - cultural artifacts
        - books
        - pornograhy
        - piston bellows
        - glass
        - cement
        - stills
        - lathe
        - vitreous enamel
        - screw
        - saddle
        - coins
        - lighthouse
        - mangonel / traction trebuchet
        - balista
        - catapault
        - crossbow
        - archimedes screw
        - suction pump
        - blast furnace
        - astrolabe
        - soap
        - glass window
    - Supply
        - alcohol
        - grain

### medieval age

    - Discover
        - gunpowder
        - soda ash
        - sulphuric acid
    - Social Change
    - Make / Invent
        - heavy machinery
        - fractional distillation
        - antimony
        - canon
        - rocket
        - aqua regia
        - worm drive
        - fully mechanical clock
        - cipher disk
        - bismuth
        - guillotine
        - rifling
        - laudanum
        - flintlock
    - Supply

### pre-industrial age

    - Discover
        - physics
        - calculus
    - Social Change
    - Make / Invent
        - mass printed media
        - vacuum pump
        - nickel
        - hydrogen
        - chlorine
        - molybdenum
        - tungsten
        - threshing machine
        - uranium
        - Leblanc process
        - microscope (when?)
    - Supply

### industrial age

    - Discover
        - chemistry
        - electricity
        - electrolosis
        - Maxwell's equations
        - medicine
        - pasturisation
        - standard model of physics
    - Social Change
        - mass migration from farms to factories
        - job unheaval / change in availability
        - workers rights movements
        - rise of the billionaires
    - Make / Invent
        - steam power
        - internal combustion engine
        - refrigeration
        - factories
        - basic communications
        - safe lighting and heating
        - automatic flour mill
        - sewing machine
        - cotton gin
        - jacquard loom
        - morphine
        - potasium
        - iodine
        - silicon
        - electro-magnets
        - portland cement
        - aluminium
        - photography
        - electric motor
        - AC/DC
        - induction coil
        - electric light
        - railway semaphore signal
        - computer program (can't run on anything yet)
        - rifled musket
        - dirigible
        - cocaine
        - amphetamines
        - heroine
        - TNT
        - gattling gun
        - dynamite
        - centrifuge
        - offset printing
        - four stroke engine
        - two stroke engine
        - gasoline
        - chromosomes
        - neodymium
        - gemanium
        - steam turbine
        - wind turbine
        - pnumatic tire
        - tractor
        - rotary engine
        - parabolic antenna
        - radio waves
        - phonograph
        - newspapers
        - ammonia, Haber process
        - x-ray
        - radioactivity
        - oscilloscope
        - electron
        - cathode ray tube
        - valves
        - chromatography
        - airplane
        - tank
        - cryptography
        - sonar
        - microphones
        - LED
        - magnetic tape
    - Supply

### post-industrial age

    - Discover
    - Social Change
        - more leisure time
    - Make / Invent
        - television
        - Turing machine
        - scanning electron microscope
        - programmable electronic computer
        - video game
        - JFET
        - MOSFET
        - transistor
        - pacemaker
        - drones
        - MOS SRAM
        - optical fibre
        - Eliza chatbot
        - pocket calculator
        - electronic watch
        - networks
        - internet
        - mobile phone
        - microprocessors
        - mobile device
        - touchscreen
        - EEPROM
        - microcomputer
        - DNA sequencing
        - synthetic drugs
        - microwave ovens
        - conveniences
        - wifi
        - radar
        - nuclear weapons
        - nuclear power
    - Supply

### information age

    - Discover
    - Social Change
        - social and political schism / division
        - world wide exchange of ideas
        - post truth
        - astro-turfing
        - bot farms
        - troll farms
        - quantum computing
        - particle accelerator
    - Make / Invent
        - computers
        - computer games
        - design tools e.g. CAD
        - databases
        - spreadsheets
        - word processing
        - CAT scan
        - MRI
        - Simulation software
    - Supply

### AI age

    - Discover
    - Social Change
        - mass unemployment
        - widespread poverty
        - social unrest
        - the singularity
        - faster pace of development
    - Make / Invent
        - AI slop
    - Supply

### space age

    - Discover
    - Social Change
    - Make / Invent
        - satelites
        - space station
        - moonshot
        - marsshot
        - space tourism
    - Supply

### space colonisation age

    - Discover
    - Social Change
        - disapora
        - terraforming
    - Make / Invent
        - space shipping
        - asteroid mining
        - ice "mining" in the ice belt
        - terraforming equipment
    - Supply

### sublimation

    - Discover
    - Social Change
        - we're done with this material world of illusions
    - Make / Invent
        - nothing
    - Supply
        - nothing

By tailoring the markets to their current needs it can make it more interesting
and a little
more coherent.

NOTE: They might be in two stages at once or overlapping from one to another.
They are not exclusive and a
direct line forward.

# Major Categories of Advancement

    - agriculture
  - industry
  - commerce
  - chemistry
  - math
  - physics
  - arts
  - culture
  - literature
  - computing
  - communications
  - information

## Stock Exchange

Consider writing a fully fledged exchange system in GoLang. It should be capable
of serving several hundred transactions
concurrently. It could be fleshed out later if needed. This can be self hosted
and be an optional component allowing
guilds of players or groups to have server level infrastructure.

Game server is responsible to write transactions. Client is allowed read
transactions.

## Conversations

Should we be able to talk over a CB style interface when at truck stops or
popular routes?

Good way to impart some lore or exposition on a planetary system.

Should have their own creole.

## Miscellaneous

Corruption Index: 0 - 100

With zero being complete corruption and 100 being none. There is a 
real-world version of this which might help to categorise trade stations and 
planets.

Shipping costs:

Calculated using the volume expressed in cubic metres, and the item's 
density. This might become an approximate for things that are not simple 
like liquids and powders e.g. toys, weapons.

## References

[Periods and Eras](https://www.weaversnest.org/human-history/periods-and-eras)

[Human Tech Tree](https://www.historicaltechtree.com/)