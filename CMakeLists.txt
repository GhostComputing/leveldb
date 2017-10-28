cmake_minimum_required(VERSION 3.7)
project(leveldb)

set(CMAKE_CXX_STANDARD 11)

# Only support build on Linux
add_definitions(-DLEVELDB_PLATFORM_POSIX)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(LEVELDB_SRC
        db/builder.cc
        db/c.cc
        db/db_bench.cc
        db/db_impl.cc
        db/db_iter.cc
        db/dbformat.cc
        db/dumpfile.cc
        db/filename.cc
        db/leveldbutil.cc
        db/log_reader.cc
        db/log_writer.cc
        db/memtable.cc
        db/repair.cc
        db/table_cache.cc
        db/version_edit.cc
        db/version_set.cc
        db/write_batch.cc

        table/block.cc
        table/block_builder.cc
        table/filter_block.cc
        table/format.cc
        table/iterator.cc
        table/merger.cc
        table/table.cc
        table/table_builder.cc
        table/two_level_iterator.cc

        util/arena.cc
        util/bloom.cc
        util/cache.cc
        util/coding.cc
        util/comparator.cc
        util/crc32c.cc
        util/env.cc
        util/env_posix.cc
        util/filter_policy.cc
        util/hash.cc
        util/histogram.cc
        util/logging.cc
        util/options.cc
        util/status.cc

        port/port_posix.cc
    )

set(EXAMPLE_SRC example/example.cc)

add_library(leveldb STATIC ${LEVELDB_SRC})

add_executable(example ${EXAMPLE_SRC})
target_link_libraries(example leveldb pthread)