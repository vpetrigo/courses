#!/bin/bash

CONTAINER_NAME=postgres-task

docker run --rm --name ${CONTAINER_NAME} -d -p 5432:5432 -v $(pwd):/workspace postgres:9.6
sleep 15
docker exec ${CONTAINER_NAME} psql -U postgres -f /workspace/schema.sql
docker exec ${CONTAINER_NAME} psql -U postgres -f /workspace/data.sql
