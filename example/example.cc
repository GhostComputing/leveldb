#include <iostream>
#include <sstream>
#include <string>

#include "leveldb/db.h"

int main()
{
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    std::string db_path("/tmp/testdb");

    leveldb::Status status = leveldb::DB::Open(options, db_path, &db);

    if (!status.ok()) {
        std::cerr << "Unable to open/create test database " << db_path << std::endl;
        std::cerr << status.ToString() << std::endl;
        return -1;
    }

    // Add 256 values to database
    leveldb::WriteOptions writeOptions;
    for (unsigned int i = 0; i != 256; ++i) {
        std::ostringstream keyStream;
        keyStream << "Key-" << i;

        std::ostringstream valueStream;
        valueStream << "Value-" << i;

        std::cout << "Write=> Key: " << keyStream.str() << ", Value: " << valueStream.str() << std::endl;
        db->Put(writeOptions, keyStream.str(), valueStream.str());
    }

    // Iterate over each item in the database and print them
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << " : " << it->value().ToString() << std::endl;
    }

    if (!it->status().ok()) {
        std::cerr << "An error was found during the scan" << std::endl;
        std::cerr << it->status().ToString() << std::endl;
    }

    delete it;
    delete db;
}
