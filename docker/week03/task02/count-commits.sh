#!/bin/bash

#!/bin/bash

commits_cnt=0

while read repo; do
	git clone $repo --branch master cloned &> /dev/null

	if [[ -d cloned && `ls -A cloned` ]]; then
		cd cloned
		let commits_cnt+=`git log --since="00:00:00 01/01/2016" --until="23:59:00 12/31/2016" --oneline | wc -l`
		cd ..
	fi

	rm -rf cloned
	printf "Current number of commits %d\n" $commits_cnt
done < repos.txt
