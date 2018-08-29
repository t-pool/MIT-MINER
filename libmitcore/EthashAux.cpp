/*
	This file is part of cpp-mitereum.

	cpp-mitereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-mitereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-mitereum.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MitashAux.h"

#include <mitash/mitash.hpp>

using namespace dev;
using namespace mit;

Result MitashAux::eval(int epoch, h256 const& _headerHash, uint64_t _nonce) noexcept
{
    auto headerHash = mitash::hash256_from_bytes(_headerHash.data());
    auto& context = mitash::get_global_epoch_context(epoch);
    auto result = mitash::hash(context, headerHash, _nonce);
    h256 mix{reinterpret_cast<byte*>(result.mix_hash.bytes), h256::ConstructFromPointer};
    h256 final{reinterpret_cast<byte*>(result.final_hash.bytes), h256::ConstructFromPointer};
    return {final, mix};
}