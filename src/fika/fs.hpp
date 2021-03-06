#pragma once
#ifndef FIKA_FS_HPP
#define FIKA_FS_HPP

#include "fika/string.hpp"

namespace fika {
    // TODO: Not sure if this implmenetation is really the... best...

    typedef String Path;
    class Location {
    };
    class FileSystemEntryState {
    public:
        int reference_count = 0;

        virtual bool move(Location other) = 0;
        virtual bool move(Location other, String newName) = 0;
        virtual bool rename(class String newName) = 0;

        virtual void open() = 0; 
        virtual void close() = 0;

        virtual class FileSystemEntry *entry(String entryName) = 0;

        virtual ~FileSystemEntryState() {};
    };
    class FileSystemEntry {
    public:
        bool move(Location other);
        bool move(Location other, String newName);
        bool rename(class String newName);
        virtual ~FileSystemEntry() {
            if (0 == --state->reference_count) {
                delete state;
            }
        }
        FileSystemEntry(FileSystemEntryState *state)
        : state(state) {
            state->reference_count++;
        }
    protected:
        FileSystemEntryState *state;
    };
    class File : public FileSystemEntry {
    public:
        
        File(FileSystemEntryState *state)
        : FileSystemEntry(state) {

        }
    };
    class Directory : public FileSystemEntry, Location {
        FileSystemEntry entry(String entryName);
        Directory(FileSystemEntryState *state)
        : FileSystemEntry(state) {

        }
    };
    class Nonexistent : public FileSystemEntry {
    public:
        Nonexistent(FileSystemEntryState *state)
        : FileSystemEntry(state) {

        }
    };
    class VirtualFileSystem {
    public:
        class EntryResource {
        public:
            int reference_count = 0;
            virtual class Directory *directory() {
                return nullptr;
            }
            virtual class File *file() {
                return nullptr;
            }
            virtual bool exists() {
                return false;
            }
            virtual bool move(Location other) {
                (void)other;
                return false;
            }
            virtual bool move(Location other, String newName) {
                (void)other;
                (void)newName;
                return false;
            }
            virtual bool rename(class String newName) {
                (void)newName;
                return false;
            }
            virtual ~EntryResource() {};
        };
        class Entry {
        public:
            class Directory *directory() {
                return resource->directory();
            }
            class File *file() {
                return resource->file();
            }
            bool exists() {
                return resource->exists();
            }
            bool move(Location other) {
                return resource->move(other);
            }
            bool move(Location other, String newName) {
                return resource->move(other, newName);
            }
            bool rename(class String newName) {
                return resource->rename(newName);
            }
            Entry(const Entry &other)
            : resource(other.resource) {

            }
            Entry(EntryResource *resource)
            : resource(resource) {
                resource->reference_count++;
            }
            ~Entry() {
                if (0 == --resource->reference_count) {
                    delete resource;
                }
            }
        private:
            EntryResource *resource;
        };
        class Directory {
        public:
            Entry entry(String entryName);
        };
        class File {
        public:
            // TODO: There should be a way to get a InputOutputStream here.
            void open();
            void close();
        };

        virtual Entry entry(Path path) = 0;
    };
    template<class ER>class FileSystemImplementation : public VirtualFileSystem {
    public:
        virtual Entry entry(Path path) override {
            return Entry(new ER(path));
        }
    };
    extern VirtualFileSystem &fs;

}

#endif