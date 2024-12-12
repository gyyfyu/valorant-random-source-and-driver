#include "imports.h"

auto cachethread() -> void
{
	auto pml4base = driver.pml4_base();
	printf( "pml4base: 0x%p\n", pml4base);

	while (true)
	{
		auto uworld = driver.read< uintptr_t >( pml4base + offsets::uworld );
		printf( "uworld: 0x%p\n", uworld );

		auto ulevel = driver.read< uintptr_t >( uworld  + offsets::ulevel );
		printf( "ulevel: 0x%p\n", ulevel );

		auto persistent_level = driver.read< uintptr_t >(uworld + 0x38);
		auto actor_count = driver.read< uintptr_t >(persistent_level + 0xA8);

		printf("actor count: %lx\n", actor_count);

		auto gamestate = driver.read< uintptr_t >( uworld + offsets::gamestate );
		printf( "gamestate: 0x%p\n", gamestate );

		Sleep( 2000 );
	}
}

auto main() -> const NTSTATUS
{
	auto process = utils::getprocessid( L"VALORANT-Win64-Shipping.exe" );

	printf( "processid: %i\n", process );

	if ( process != 0 )
	{
		driver.initdriver( process );
		cachethread();
		//std::thread(cachethread).detach();
	}

	auto p = getchar();
	return 0;
}
