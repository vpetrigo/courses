CREATE TABLE conference (name text, description text, primary key (name));
CREATE TABLE venue (id integer primary key, name text, city text, country text, lat numeric(7,5), lon numeric(8,5),unique(name,city,country), unique(lat,lon));
CREATE TABLE papersubmission(id integer primary key, conference text, year integer, title text, isbn text, page integer, venue_id integer,unique(conference,year,title), unique (conference,year<Plug>PeepOpenage),foreign key (conference) references conference (name), foreign key (venue_id) references venue (id));
