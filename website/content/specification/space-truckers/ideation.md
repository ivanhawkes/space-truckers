---
author: Ivan Hawkes
categories:
  - Documentation
  - Concept
  - Idea
date: '2026-06-07'
description:
  A document that briefyly describes the goals and intents of this project.
title: Ideation
type: specification
---

# Ideas for the development of my blog site

## Purpose

The purpose of this document is to state quite clearly the idea that will be
further developed into a project.

## Logline

Describe in a single sentance the purpose of this project.

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

You can go fast or you can go cheap, but you can't go both. Fuel burns at the
start and end of journeys will need to be
factored into the price of goods.

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

Each community will have it's own level of tech advancement based on it's
resources available,
population (skills, health, etc), and past achievements.

They will need to trade for materials / tech that can help advance them through
a tech tree.

NOTE: each period builds on previous periods. Some goods will drop in value at
the start of
the next period, others are evergreen and persist for the rest of the tree. By
default,
anything they make is also considered available for sale.

Rough plan:

- stone age - good for looters and slavers to set up trade posts
    - SOCIAL CHANGE
    - MAKE
        - religion
        - fire
        - stone tools
        - rope
        - charcoal
        - domesticated dogs
        - pottery
        - pigments
        - cave painting
        - glue
        - mining
    - SELL
        - slaves
        - natural drugs
        - precursors for biotech weapons i.e. novel viruses
    - BUY
        - small amounts of luxury lifestyle goods for the slavers
        - colonisation goods e.g. habitats
        - weapons
        - restraints
        - alcohol
        - drugs
        - sex workers
- pre-history
    - SOCIAL CHANGE
    - MAKE
        - bread
        - fermentation
        - domesticated grains
        - domesticated animals
        - mud bricks
        - lime
        - lead
        - ard plough
        - irrigation
    - SELL
    - BUY
- copper
    - SOCIAL CHANGE
    - MAKE
        - salt mining
        - sailing (exploration)
        - crucible
        - fired bricks
        - natron
        - plumbing
        - mirrors
    - SELL
    - BUY
- bronze age - much the same as above
    - SOCIAL CHANGE
    - MAKE
        - wheel
    - SELL
        - metals
        - minerals
        - jewelery
        - cloth / clothing
        - mercenaries
    - BUY
        - pen + paper
        - engineering items - building pyramids / ziggurats
- iron age
    - SOCIAL CHANGE
        - rise of the kings
    - MAKE
        - early farming implements
        - carts drawn by animals
        - latrines
        - swords
        - writing
        - tin
        - bronze
        - brass
        - vinegar
        - shaduf
        - paper
        - pen / quill
        - papyrus
        - ink
    - SELL
        - harder metals
    - BUY
        - advance farming implements
- classical age
    - SOCIAL CHANGE
        - world conquest
    - MAKE
        - maths
        - alchemy
        - shipping
        - water clock
        - star charts
        - Antikythera mechanism / analogue computer
        - orary
        - ceramincs
        - mills
        - siege weapons
        - art / theatre
        - cultural artifacts
        - books
        - pornograhy
        - piston bellows
        - glass
        - concrete
        - distillation
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
    - SELL
        - grain
        - alcohol
    - BUY
- medieval
    - SOCIAL CHANGE
    - MAKE
        - heavy machinery
        - fractional distillation
        - soda ash
        - antimony
        - gunpowder
        - compass
        - sulphuric acid
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
        - flintlock / black powder gun
    - SELL
    - BUY
- pre-industrial
    - SOCIAL CHANGE
    - MAKE
        - physics
        - mass printed media
        - vacuum pump
        - calculus
        - nickel
        - hydrogen
        - chlorine
        - molybdenum
        - tungsten
        - threshing machine
        - uranium
        - Leblanc process
        - microscope (when?)
    - SELL
    - BUY
- industrial
    - SOCIAL CHANGE
        - job unheaval / change in availability
        - workers rights movements
        - rise of the billionaires
    - MAKE
        - steam power
        - internal combustion engine
        - refrigeration
        - factories
        - basic communications
        - electricity
        - safe lighting and heating
        - early medicine
        - chemistry
        - automatic flour mill
        - sewing machine
        - cotton gin
        - electrolosis
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
        - pasturisation
        - dynamite
        - Maxwell's equations
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
        - standard model of physics
        - chromatography
        - airplane
        - tank
        - cryptography
        - sonar
        - microphones
        - LED
        - magnetic tape
    - SELL
    - BUY
- post-industrial
    - SOCIAL CHANGE
        - more leisure time
    - MAKE
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
    - SELL
    - BUY
- information age
    - SOCIAL CHANGE
        - social and political schism / division
        - world wide exchange of ideas
        - post truth
        - astro-turfing
        - bot farms
        - troll farms
        - quantum computing
        - particle accelerator
    - MAKE
        - computers
        - computer games
        - design tools e.g. CAD
        - databases
        - spreadsheets
        - word processing
        - CAT scan
        - MRI
        - Simulation software
    - SELL
    - BUY
- AI age
    - SOCIAL CHANGE
        - mass unemployment
        - widespread poverty
        - social unrest
        - the singularity
        - faster pace of development
    - MAKE
        - AI slop
    - SELL
    - BUY
- space age
    - SOCIAL CHANGE
    - MAKE
        - satelites
        - space station
        - moonshot
        - marsshot
        - space tourism
    - SELL
    - BUY
- space colonisation
    - SOCIAL CHANGE
        - disapora
        - terraforming
    - MAKE
        - space shipping
        - asteroid mining
        - ice "mining" in the ice belt
        - terraforming equipment
    - SELL
    - BUY
- sublimation
    - SOCIAL CHANGE
        - we're done with this material world of illusions
    - MAKE
        - nothing
    - SELL
        - nothing
    - BUY
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

## References

[Periods and Eras](https://www.weaversnest.org/human-history/periods-and-eras)

[Human Tech Tree](https://www.historicaltechtree.com/)