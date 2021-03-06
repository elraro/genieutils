/*
    genie/dat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2013  Armin Preiml
    Copyright (C) 2011 - 2017  Mikko "Tapsa" P

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genie/dat/SoundItem.h"
#include <string.h>

namespace genie
{

SoundItem::SoundItem()
{
}

SoundItem::~SoundItem()
{
}

//------------------------------------------------------------------------------
void SoundItem::setGameVersion(GameVersion gv)
{
  ISerializable::setGameVersion(gv);
}

unsigned short SoundItem::getFileNameSize()
{
  if (getGameVersion() < GV_SWGB)
    return 13;
  return 27;
}

void SoundItem::serializeObject(void)
{
  GameVersion gv = getGameVersion();

  serialize(FileName, getFileNameSize());

  if (gv < GV_TEST)
  {
    int16_t res = ResourceID;
    serialize<int16_t>(res);
    ResourceID = res;
  }
  else
  {
    serialize<int32_t>(ResourceID);
  }
  serialize<int16_t>(Probability);

  if (gv >= GV_AoKE3)
  {
    serialize<int16_t>(Civilization);
    serialize<int16_t>(IconSet);
  }
}

}
