---
author: Ivan Hawkes
date: '2026-05-07'
description: Requirements Specification
title: Requirements Specification
type: specification
---

# Requirements Specification

A description of what constitutes a requirement specification.

## Space Truckers SDK

The Space Truckers SDK will be written in c++ and using Unreal
Engine 5.7.x for the framework. Its purpose is to facilitate the
creation of space bound trading games.

It will provide support code that allows spaceships to travel the galaxy 
from one planet to another and trade with the entities who live there.

The game will use three-dimensional assets but play in a two-dimensional 
game field.

The product should avoid use of technologies that will prevent it from being 
deployed on all the available platforms.

## Minimum Viable Product (MVP)

[Epic](../kanban/epics/ep-001-minimum-viable-product.md)

The first step of development, after requirements gathering, will be to 
produce a minimum viable product (MVP).

Included in the MVP will be the following features:

1. The game will automatically play itself with no user interaction.
2. At the start of the game, the computer will generate a random universe. 
   - 100 planets
   - each planet will have a marketplace
   - each marketplace will have a random sample of products from a table
   - a ship will be spawned at the origin point 0, 0, 0
   - the ship will randomly choose a planet and start moving towards it
   - once in range of the planet it will enter an orbit
   - the ship may query the marketplace for goods to exchange
   - the ship and merchant will exchange goods and funds in a near random manner
   - the merchant, being an NPC construct will be funded by the PC in 
     between turns, slowly regaining products and cash
   - if the planet has spaceship fuel the ship should purchase enough to 
     refill its tanks
   - any actions undertaken will be written to the log file
   - these steps will repeat ad infinitum

### Requirements

List them out. Link them to Kanbans when appropriate.